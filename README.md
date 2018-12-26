# SCREEN EXPANSION PROJECT

THe purpose of this project is to make two screens work as a single one, with the screen coming out of
the rigth screen, entering the left one. After "leaving" the left screen it should loop back.

We created a library to work with the LCD1602A LCD display, using the SPI and I2C communication protocols.
Afterwards, we implemented EEPROM,FLASH and SRAM memory tests to verify the proper behaviour of those memories.

If one of those memories fails, program execution shall be halted and an error message will appear on one of the screens.
