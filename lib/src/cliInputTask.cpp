//
// Created by matt on 4/5/23.
//

#include <Arduino.h>
#include "cliInputTask.h"

void cliInputTask(void *parameter) {
    char buffer[20];
    char c;
    int i = 0;
    while(1) {
        //Delay to avoid watchdog
        vTaskDelay(10 / portTICK_PERIOD_MS);
        if (Serial.available() > 0) {
            c = Serial.read();
            buffer[i] = c;
            i++;
            if (c == '\n') {
                //Sets the newline character in buffer to a null terminator
                buffer[i - 2] = '\0';
                //Sends the buffer to the input queue and resets buffer and i accordingly
                if (xQueueSend(inputQueue, buffer, 0) == pdFALSE) Serial.println("Something went wrong!");
                if (strstr(buffer, "led ")) {
                    xQueueSend(ledQueue, buffer + 4, 0);
                }
                if (strstr(buffer, "help")) {
                    Serial.println("Available commands are:");
                    Serial.println("led [red][green][blue][yellow] on");
                    Serial.println("led [red][green][blue][yellow] off");
                    Serial.println("led all on");
                    Serial.println("led all off");
                }
                memset(buffer, 0, 20);
                i = 0;
            }
        }
    }
}


