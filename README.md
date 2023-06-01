# CLI Project

This is a very simple project that uses serial input and a shock detector to influence tasks relating to LED toggling, displaying information on an OLED display, using a temperature sensor, and triggering an ISR with a deferred interrupt.

The main features of this project include:

1. **OLED SPI Information Display.** The display has three separate areas for displaying: the status of each LED, temperature and humidity values, and all serial input.
2. **LED Toggling.** There are five LEDs in this project and four of them can be toggled with serial commands. The LEDs can be toggled individually, or all at once, and each LED's status will be reflected on the display. 
3. **Temperature & Humidity Reading.** Every second, the room's temperature and humidity is read and shown on the display.
4. **Deferred Interrupts.** When a shock is detected, interrupts will be deferred to the display and LED tasks. The LEDs will blink on and off during the interrupt and the display will blink an message that an interrupt occurred.

## OLED SPI Information Display
Display Overview  | Serial Input Display
------------- | -------------
<img src="https://github.com/mattwheatley98/CLI-Project/assets/113391095/1c145805-81d4-4fd0-b58a-280c40789594" width = 350 height = 700>  |  <img src="https://github.com/mattwheatley98/CLI-Project/assets/113391095/0fc2f2b7-7bcc-4163-94cd-a94bca3e6975" width = 350 height = 700>

## LED Toggling
Individual LED Toggling  | Group LED Toggling
------------- | -------------
<video src="https://github.com/mattwheatley98/CLI-Project/assets/113391095/e1a52fc7-449e-4fd5-ba61-b65659688a8e" width = 350 height = 700>  |  <video src="https://github.com/mattwheatley98/CLI-Project/assets/113391095/a22d338d-afda-4f2b-85e5-cca19ebe8173" width = 350 height = 700>

## Temperature & Humidity Reading
Read Temperature & Humidity  | 
------------- |
<video src="https://github.com/mattwheatley98/CLI-Project/assets/113391095/d2a89756-ffab-423d-84e2-88dfaa5359ad" width = 350 height = 700>  |  

## Deferred Interrupts
Detecting Shock |
------------- |
<video src="https://github.com/mattwheatley98/CLI-Project/assets/113391095/7fd282a0-2e31-4d9c-9d79-c01f73efa59b" width = 350 height = 700>  |
