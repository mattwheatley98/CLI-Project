//
// Created by matt on 4/7/23.
//

#include <Arduino.h>
#include </home/matt/CLionProjects/CLIProject/.pio/libdeps/esp32dev/U8g2/src/U8g2lib.h>
#include "displayTask.h"
#define OLED_DC 4
#define OLED_CS 5
#define OLED_RES 2

void displayInput(char *buffer, char *redStatus, char *greenStatus, char *blueStatus, char *yellowStatus);

void displayTask(void *parameter) {
    U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RES);
    u8g2.begin();

    char buffer[20];
    char redStatus[] = "OFF";
    char greenStatus[] = "OFF";
    char blueStatus[] = "OFF";
    char yellowStatus[] = "OFF";

    while (1) {
        displayInput(buffer, redStatus, greenStatus, blueStatus, yellowStatus);

        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_ncenB08_tr);

        u8g2.setCursor(0, 15);
        u8g2.print("Red");
        u8g2.setCursor(0, 25);
        u8g2.print(redStatus);

        u8g2.setCursor(30, 15);
        u8g2.print("Grn");
        u8g2.setCursor(30, 25);
        u8g2.print(greenStatus);

        u8g2.setCursor(0, 50);
        u8g2.print("Blu");
        u8g2.setCursor(0, 60);
        u8g2.print(blueStatus);

        u8g2.setCursor(30, 50);
        u8g2.print("Ylw");
        u8g2.setCursor(30, 60);
        u8g2.print(yellowStatus);

        //Vertical line
        u8g2.drawLine(56, 0, 56, 60);
        //Horizontal line
        u8g2.drawLine(56, 32, 0, 32);

        u8g2.sendBuffer();
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