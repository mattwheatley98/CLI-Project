//
// Created by matt on 4/7/23.
//

#include <Arduino.h>
#include </home/matt/CLionProjects/CLIProject/.pio/libdeps/esp32dev/U8g2/src/U8g2lib.h>
#include "displayTask.h"
#include "cliDispatcherTask.h"

#define OLED_DC 4
#define OLED_CS 5
#define OLED_RES 2

void displayInput(char *buffer, char *redStatus, char *greenStatus, char *blueStatus, char *yellowStatus);

void displayTask(void *parameter) {
    U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI display(U8G2_R0, OLED_CS, OLED_DC, OLED_RES);
    display.begin();

    char buffer[20];
    char messageBuffer[20] = "";
    char redStatus[] = "OFF";
    char greenStatus[] = "OFF";
    char blueStatus[] = "OFF";
    char yellowStatus[] = "OFF";

    while (1) {
        if (xSemaphoreTake(interruptDisplaySemaphore, 0) == pdTRUE) {
            display.clearBuffer();
            display.setFont(u8g2_font_ncenB08_tr);

            for (int i = 0; i < 4; ++i) {
                display.clearBuffer();
                display.sendBuffer();
                vTaskDelay(125 / portTICK_PERIOD_MS);
                display.setCursor(30, 30);
                display.print("INTERRUPT");
                display.setCursor(35, 45);
                display.print("DETECTED");
                display.sendBuffer();
                vTaskDelay(125 / portTICK_PERIOD_MS);
            }
            strcpy(redStatus, "OFF");
            strcpy(greenStatus, "OFF");
            strcpy(blueStatus, "OFF");
            strcpy(yellowStatus, "OFF");
        } else {
            display.clearBuffer();
            display.setFont(u8g2_font_ncenB08_tr);
            displayInput(buffer, redStatus, greenStatus, blueStatus, yellowStatus);
            if (xQueueReceive(messageQueue, messageBuffer, 0) == pdTRUE) {}
            display.setCursor(0, 15);
            display.print("Red");
            display.setCursor(0, 25);
            display.print(redStatus);

            display.setCursor(30, 15);
            display.print("Grn");
            display.setCursor(30, 25);
            display.print(greenStatus);

            display.setCursor(0, 50);
            display.print("Blu");
            display.setCursor(0, 60);
            display.print(blueStatus);

            display.setCursor(30, 50);
            display.print("Ylw");
            display.setCursor(30, 60);
            display.print(yellowStatus);

            //Temp/Humid
            display.setCursor(62, 15);
            display.print("Tmp:");
            display.setCursor(96, 15);
            display.print("10F");
            display.setCursor(62, 25);
            display.print("Hmd:");
            display.setCursor(96, 25);
            display.print("100");

            display.setCursor(62, 52);
            display.print(messageBuffer);


            //Vertical line
            display.drawLine(56, 0, 56, 60);
            //Horizontal line
            display.drawLine(128, 32, 0, 32);

            display.sendBuffer();
        }
    }
}

void displayInput(char *buffer, char *redStatus, char *greenStatus, char *blueStatus, char *yellowStatus) {
    if (xQueueReceive(displayQueue, buffer, 0) == pdTRUE) {
        if (strcmp(buffer, "red on") == 0) {
            strcpy(redStatus, "ON");
        }
        if (strcmp(buffer, "red off") == 0) {
            strcpy(redStatus, "OFF");
        }
        if (strcmp(buffer, "green on") == 0) {
            strcpy(greenStatus, "ON");
        }
        if (strcmp(buffer, "green off") == 0) {
            strcpy(greenStatus, "OFF");
        }
        if (strcmp(buffer, "blue on") == 0) {
            strcpy(blueStatus, "ON");
        }
        if (strcmp(buffer, "blue off") == 0) {
            strcpy(blueStatus, "OFF");
        }
        if (strcmp(buffer, "yellow on") == 0) {
            strcpy(yellowStatus, "ON");
        }
        if (strcmp(buffer, "yellow off") == 0) {
            strcpy(yellowStatus, "OFF");
        }
        if (strcmp(buffer, "all on") == 0) {
            strcpy(redStatus, "ON");
            strcpy(greenStatus, "ON");
            strcpy(blueStatus, "ON");
            strcpy(yellowStatus, "ON");
        }
        if (strcmp(buffer, "all off") == 0) {
            strcpy(redStatus, "OFF");
            strcpy(greenStatus, "OFF");
            strcpy(blueStatus, "OFF");
            strcpy(yellowStatus, "OFF");
        }
    }
}