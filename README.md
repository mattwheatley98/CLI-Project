# CLI Project

This is a very simple project that uses serial input and a shock detector to influence tasks relating to LED toggling, displaying information on an OLED display, using a temperature sensor, and triggering an ISR and deferring its interrupt.

The main features of this project are as follows:

1. **OLED SPI Information Display.** The display has three separate areas for displaying: the status of each LED, read temperature and humidity values, and all serial input.
2. **LED Toggling.** There are five LEDs in this project and four of them can be toggled with serial commands. The LEDs can be toggled individually, or all at once, and each LEDs status will be reflected on the display. 
3. **Temperature & Humidity Reading.** Every quarter second, the current area's temperature and humidity is read and shown on the display.
4. **Deferred Interrupts.** When a shock is detected, interrupts will be deferred to the display and LED tasks. The display will begin blinking a message that an interrupt occurred, while the LEDs blink in tandem.

## OLED SPI Information Display
Display Overview  | Serial Input Display
------------- | -------------
<img src="GIF HERE" width = 350 height = 700>  |  <img src="GIF HERE" width = 350 height = 700>

## LED Toggling
Individual LED Toggling  | Group LED Toggling
------------- | -------------
<img src="GIF HERE" width = 350 height = 700>  |  <img src="GIF HERE" width = 350 height = 700>

## Temperature & Humidity Reading
Read Temperature & Humidity  | 
------------- |
<img src="GIF HERE" width = 350 height = 700>  |  

## Deferred Interrupts
Detecting Shock |
------------- |
<img src="GIF HERE" width = 350 height = 700>  |
