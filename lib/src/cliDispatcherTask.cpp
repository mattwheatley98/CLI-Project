//
// Created by matt on 4/5/23.
//

#include <Arduino.h>
#include "cliDispatcherTask.h"
#include "cliInputTask.h"

void cliDispatcherTask(void *parameter) {
    char buffer[20];

    while (1) {
        if (xQueueReceive(inputQueue, buffer, 0) == pdTRUE) {
            xQueueSend(messageQueue, buffer, 0);
            if (strstr(buffer, "buzz ")) {
                xQueueSend(buzzQueue, buffer + 5, 0);
            } else if (strstr(buffer, "led ")) {
                xQueueSend(ledQueue, buffer + 4, 0);
            }
        }
    }
}