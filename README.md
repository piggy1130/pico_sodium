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
* **Command**:  
makedir build  
cd build  
cmake ..  
make -j4  

* **Push file to Pico**
  button -- easy

  non-button  
1. need wire pi and pico based on the guidance book
2. check the device connect to pico is pi4 or pi5, with different command
   


sudo openocd -f ~/pico/pico/raspberrypi5-swd.cfg -f target/rp2040.cfg -c "program blink.elf verify reset exit"  
