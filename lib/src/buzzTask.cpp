//
// Created by matt on 4/6/23.
//

#include <Arduino.h>
#include "cliDispatcherTask.h"

void buzzTask (void *parameter) {
    char buffer[20];
    while (1) {
        if (xQueueReceive(buzzQueue, buffer, 0) == pdTRUE) {
            Serial.print("From buzz: ");
            Serial.println(buffer);
        }
    }
}