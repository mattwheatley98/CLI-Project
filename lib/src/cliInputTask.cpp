//
// Created by matt on 4/5/23.
//

#include "cliInputTask.h"
#include <Arduino.h>

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
                buffer[i - 2] = '\0';
                //Serial.println(buffer);
                if (xQueueSend(inputQueue, &buffer, 0) == pdTRUE) {
                    Serial.println("Successfully sent to queue!");
                } else {
                    Serial.println("Something went wrong!");
                }
                memset(buffer, 0, 20);
                i = 0;
            }
        }
    }
}


