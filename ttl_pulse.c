#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

#define TTL_IN_PIN   28   // GP28 input: falling edge trigger
#define PULSE_OUT    27   // GP27 output: 10 us pulse
#define DELAY_US     1000 // 1 ms delay
#define PULSE_US     10   // 10 us pulse width

volatile uint64_t t0_us = 0;
volatile alarm_id_t start_alarm = -1;
volatile alarm_id_t stop_alarm  = -1;

// Turn OFF pulse (set GP27 low)
int64_t pulse_off_cb(alarm_id_t id, void *user_data) {
    (void)id; (void)user_data;
    gpio_put(PULSE_OUT, 0);
    stop_alarm = -1;
    return 0; // one-shot
}

// Turn ON pulse (set GP27 high), then schedule OFF after 10 us
int64_t pulse_on_cb(alarm_id_t id, void *user_data) {
    (void)id; (void)user_data;

    gpio_put(PULSE_OUT, 1);

    // Schedule turning it back off after 10 us
    stop_alarm = add_alarm_in_us(PULSE_US, pulse_off_cb, NULL, false);

    start_alarm = -1;
    return 0; // one-shot
}

// GPIO ISR: detect falling edge on GP28, record t0, schedule pulse in 1 ms
void ttl_fall_isr(uint gpio, uint32_t events) {
    if (gpio != TTL_IN_PIN) return;
    if (!(events & GPIO_IRQ_EDGE_FALL)) return;

    t0_us = time_us_64(); // record t0 at the falling edge

    // With 8 ms period you usually don't need canceling,
    // but this makes it robust if edges come unexpectedly fast:
    if (start_alarm >= 0) {
        cancel_alarm(start_alarm);
        start_alarm = -1;
    }
    if (stop_alarm >= 0) {
        cancel_alarm(stop_alarm);
        stop_alarm = -1;
        gpio_put(PULSE_OUT, 0);
    }

    // Schedule pulse start after 1 ms
    start_alarm = add_alarm_in_us(DELAY_US, pulse_on_cb, NULL, false);
}

int main() {
    stdio_init_all();
    sleep_ms(1000);

    // Output (GP27)
    gpio_init(PULSE_OUT);
    gpio_set_dir(PULSE_OUT, GPIO_OUT);
    gpio_put(PULSE_OUT, 0);

    // Input (GP28) - TTL is 3.3 V, so direct is OK; make sure grounds are common.
    gpio_init(TTL_IN_PIN);
    gpio_set_dir(TTL_IN_PIN, GPIO_IN);
    // If the input could float, you can enable a pull-up/down. For real push-pull TTL, usually leave off.
    // gpio_pull_up(TTL_IN_PIN);

    // Enable falling-edge interrupt on GP28
    gpio_set_irq_enabled_with_callback(
        TTL_IN_PIN,
        GPIO_IRQ_EDGE_FALL,
        true,
        &ttl_fall_isr
    );

    while (true) {
        tight_loop_contents(); // interrupt-driven
    }
}
