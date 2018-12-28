# SCREEN EXPANSION PROJECT

The purpose of this project is to make two screens work as a single one, with the screen coming out of
the rigth screen, entering the left one. After "leaving" the left screen it should loop back.

We created a library to work with the LCD1602A LCD display, using the SPI and I2C communication protocols.
Afterwards, we implemented EEPROM,FLASH and SRAM memory tests to verify the proper behaviour of those memories.

If one of those memories fails, program execution shall be halted and an error message will appear on one of the screens.

## Project structure:

We have 3 different folders:

  - Board - where the schematic and PCB design are stored;
  - src - where the code is;
  - docs - where the documentation is stored.
  
# src structure:
  
  Inside this folder we find many folders, each for a different purpose:
  
    - I2C - folder in which we have a program to show the I2C protocol during the presentation;
    - SPI - folder in which we have a program to show the SPI protocol during the presentation;
    - SRAM - folder used for development of the SRAM test;
    - eeprom_write_hash - project used to write the hash to the eeprom memory address;
    - flash_test - folder used for the development of the Flash memory test;
    - hash_calc - python script to calculate the hash of a IntelHex file;
    - screen_expansion_project - the final project.
# The screen_expansion_project

Inside this folder the header files are inside the Header Files folder and the program files inside the Program Files folder.

All the files are properly named and commented, simplifying the task of reading the project's source files.
