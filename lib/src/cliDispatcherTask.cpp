//
// Created by matt on 4/5/23.
//

#include "cliDispatcherTask.h"
#include "cliInputTask.h"
#include <Arduino.h>

void cliDispatcherTask(void *parameter) {
    char buffer[20];
    while (1) {
        if(xQueueReceive(inputQueue, buffer, 0) == pdTRUE) {
            Serial.print("Received: ");
            Serial.print(buffer);
            Serial.println();
        }
    }
}