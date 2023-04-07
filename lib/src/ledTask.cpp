//
// Created by matt on 4/6/23.
//

#include <Arduino.h>
#include "cliDispatcherTask.h"

void ledTask(void *parameter) {
    char buffer[20];
    while (1) {
        if (xQueueReceive(ledQueue, buffer, 0) == pdTRUE) {
            Serial.println(buffer);
            if (strstr(buffer, "red")) {
                if (strcmp(buffer + 4, "on") == 0) {
                    digitalWrite(27, HIGH);
                    Serial.println("Red LED on!");
                } else if (strcmp(buffer + 4, "off") == 0) {
                    digitalWrite(27, LOW);
                    Serial.println("Red LED off!");
                }
            }
            if (strstr(buffer, "green")) {
                if (strcmp(buffer + 6, "on") == 0) {
                    digitalWrite(33, HIGH);
                    Serial.println("Green LED on!");
                } else if (strcmp(buffer + 6, "off") == 0) {
                    digitalWrite(33, LOW);
                    Serial.println("Green LED off!");
                }
            }
            if (strstr(buffer, "blue")) {
                if (strcmp(buffer + 5, "on") == 0) {
                    digitalWrite(26, HIGH);
                    Serial.println("Blue LED on!");
                } else if (strcmp(buffer + 5, "off") == 0) {
                    digitalWrite(26, LOW);
                    Serial.println("Blue LED off!");
                }
            }
            if (strstr(buffer, "yellow")) {
                if (strcmp(buffer + 7, "on") == 0) {
                    digitalWrite(32, HIGH);
                    Serial.println("Yellow LED on!");
                } else if (strcmp(buffer + 7, "off") == 0) {
                    digitalWrite(32, LOW);
                    Serial.println("Yellow LED off!");
                }
            }
            if (strstr(buffer, "on")) {
                digitalWrite(27, HIGH);
                digitalWrite(33, HIGH);
                digitalWrite(26, HIGH);
                digitalWrite(32, HIGH);
                Serial.println("All LEDs on!");
            }
            if (strstr(buffer, "off")) {
                digitalWrite(27, LOW);
                digitalWrite(33, LOW);
                digitalWrite(26, LOW);
                digitalWrite(32, LOW);
                Serial.println("All LEDs off!");
            }
        }
    }
}
