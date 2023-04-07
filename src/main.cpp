#include <Arduino.h>
#include </home/matt/CLionProjects/CLIProject/.pio/libdeps/esp32dev/U8g2/src/U8g2lib.h>
#include "../lib/src/cliInputTask.h"
#include "../lib/src/cliDispatcherTask.h"
#include "../lib/src/buzzTask.h"
#include "../lib/src/ledTask.h"

QueueHandle_t inputQueue;
QueueHandle_t buzzQueue;
QueueHandle_t ledQueue;

#define OLED_MOSI  23
#define OLED_CLK   18
#define OLED_DC    4
#define OLED_CS    5
#define OLED_RES 2

// Initialize the U8G2 library with the appropriate constructor for your display
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RES);

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println("---Device Control CLI---");
    Serial.println("Please enter a command, or type \"help\" for a list of them");

    u8g2.begin(); //TEST

    pinMode(33, OUTPUT); //Green
    pinMode(32, OUTPUT); // Yellow
    pinMode(27, OUTPUT); // Red
    pinMode(26, OUTPUT); // Blue
    inputQueue = xQueueCreate(3, sizeof(char) * 20);
    buzzQueue = xQueueCreate(3, sizeof(char) * 20);
    ledQueue = xQueueCreate(3, sizeof(char) * 20);


    pinMode(19, INPUT);
    digitalWrite(19, HIGH);

    xTaskCreate(
            cliInputTask,
            "CLI Input Task",
            1024,
            nullptr,
            0,
            nullptr
    );

    xTaskCreate(
            cliDispatcherTask,
            "CLI Dispatcher Task",
            1024,
            nullptr,
            0,
            nullptr
    );

    /*
    xTaskCreate(
            buzzTask,
            "Buzz Task",
            1024,
            nullptr,
            0,
            nullptr
    );
*/
    xTaskCreate(
            ledTask,
            "LED Task",
            1024,
            nullptr,
            0,
            nullptr
    );

}

void loop() {
// Clear the display
    u8g2.clearBuffer();

    // Set the font and position for the text
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0, 15);

    // Print the text to the display
    u8g2.print("Machi is baka lol");

    delay(500);
    
    // Send the buffer to the display
    u8g2.sendBuffer();

    // Wait for a moment before updating the display
    delay(1000);
}