# Guidance Book  
https://www.laskakit.cz/user/related_files/getting-started-with-pico.pdf  

# Work Procedure  
* **Step 1**:
run "pico_setup.sh" bash file.

* **Step 2**:
create a project foler - such as: "blink"

* **Step 3**:
Inside of folder:
    * create c program: "blink.c"
    * create file: "CMakeLists.txt"
* **Step 4: Command**:  
   mkdir build  
   cd build  
   cmake ..  
   make -j4  

* **Step 5:**  Push file to Pico
     * method 1: Unplug --> Holding Button --> Plug: easy but much labor work.  
     * method 2: Push file to Pico with command, need to wire lines
       <img width="518" height="316" alt="Screenshot 2025-12-16 110847" src="https://github.com/user-attachments/assets/ea7520e5-35c3-4a57-9e12-d6f721792f65" />
* **Step 6: ** Command to send file from Pi to Pico  
   * if using Rasperry Pi 5:
     command: sudo openocd -f ~/pico/pico/raspberrypi5-swd.cfg -f target/rp2040.cfg -c "program blink.elf verify reset exit"  
     <img width="800" height="326" alt="Screenshot 2025-12-16 112053" src="https://github.com/user-attachments/assets/ca1b0d60-c730-478d-aebd-3dbd5e6df3dd" />

   * if using Raspberry Pi 4:
     command: check the guidance book, something like
     <img width="537" height="40" alt="Screenshot 2025-12-16 112222" src="https://github.com/user-attachments/assets/50176ce7-1457-4875-b8a1-99a28f7ab12d" />


