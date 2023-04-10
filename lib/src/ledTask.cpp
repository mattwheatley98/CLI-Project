//
// Created by matt on 4/6/23.
//

#include <Arduino.h>
#include "cliInputTask.h"
#include "displayTask.h"
#include "ledTask.h"

void displayQueueSend(char *buffer);

//Task that deals with LED-related features and a "buzz" that goes off during the ISR
void ledTask(void *parameter) {
    char buffer[20];
    //Initializes and sets the modes for LED-related pins, as well as for the "buzz pin" used in the ISR
    pinMode(15, INPUT); //Shock pin
    pinMode(22, OUTPUT); //Buzz pin
    pinMode(33, OUTPUT); //Green
    pinMode(32, OUTPUT); // Yellow
    pinMode(27, OUTPUT); // Red
    pinMode(26, OUTPUT); // Blue

    //Activates when the ISR is triggered
    while (1) {
        if (xSemaphoreTake(interruptLedSemaphore, 0) == pdTRUE) {
            //For loop that causes the LED and "buzz" pins to pulse
            for (int i = 0; i < 4; ++i) {
                digitalWrite(27, HIGH);
                digitalWrite(33, HIGH);
                digitalWrite(26, HIGH);
                digitalWrite(32, HIGH);
                digitalWrite(22, HIGH); //BUZZ
                vTaskDelay(125 / portTICK_PERIOD_MS);
                digitalWrite(27, LOW);
                digitalWrite(33, LOW);
                digitalWrite(26, LOW);
                digitalWrite(32, LOW);
                digitalWrite(22, LOW); //BUZZ
                vTaskDelay(125 / portTICK_PERIOD_MS);
            }
        }
        //Handles signaling for the red LED
        if (xQueueReceive(ledQueue, buffer, 0) == pdTRUE) {
            if (strstr(buffer, "red")) {
                if (strcmp(buffer + 4, "on") == 0) {
                    digitalWrite(27, HIGH);
                    Serial.println("Red LED on!");
                    displayQueueSend(buffer);
                } else if (strcmp(buffer + 4, "off") == 0) {
                    digitalWrite(27, LOW);
                    Serial.println("Red LED off!");
                    displayQueueSend(buffer);
                }
            }
            //Handles signaling for the green LED
            if (strstr(buffer, "green")) {
                if (strcmp(buffer + 6, "on") == 0) {
                    digitalWrite(33, HIGH);
                    Serial.println("Green LED on!");
                    displayQueueSend(buffer);
                } else if (strcmp(buffer + 6, "off") == 0) {
                    digitalWrite(33, LOW);
                    Serial.println("Green LED off!");
                    displayQueueSend(buffer);
                }
            }
            //Handles signaling for the blue LED
            if (strstr(buffer, "blue")) {
                if (strcmp(buffer + 5, "on") == 0) {
                    digitalWrite(26, HIGH);
                    Serial.println("Blue LED on!");
                    displayQueueSend(buffer);
                } else if (strcmp(buffer + 5, "off") == 0) {
                    digitalWrite(26, LOW);
                    Serial.println("Blue LED off!");
                    displayQueueSend(buffer);
                }
            }
            //Handles signaling for the yellow LED
            if (strstr(buffer, "yellow")) {
                if (strcmp(buffer + 7, "on") == 0) {
                    digitalWrite(32, HIGH);
                    Serial.println("Yellow LED on!");
                    displayQueueSend(buffer);
                } else if (strcmp(buffer + 7, "off") == 0) {
                    digitalWrite(32, LOW);
                    Serial.println("Yellow LED off!");
                    displayQueueSend(buffer);
                }
            }
            //Handles signaling for when all LEDs are turned on
            if (strstr(buffer, "all on")) {
                digitalWrite(27, HIGH);
                digitalWrite(33, HIGH);
                digitalWrite(26, HIGH);
                digitalWrite(32, HIGH);
                Serial.println("All LEDs on!");
                displayQueueSend(buffer);
            }
            //Handles signaling for when all LEDs are turned off
            if (strstr(buffer, "all off")) {
                digitalWrite(27, LOW);
                digitalWrite(33, LOW);
                digitalWrite(26, LOW);
                digitalWrite(32, LOW);
                Serial.println("All LEDs off!");
                displayQueueSend(buffer);
            }
        }
    }
}

void displayQueueSend(char *buffer) {
    if (xQueueSend(displayQueue, buffer, 0) == pdFALSE) Serial.println("Something went wrong!");
}
