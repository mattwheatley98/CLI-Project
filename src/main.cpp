#include <Arduino.h>
#include "../lib/src/cliInputTask.h"
#include "../lib/src/cliDispatcherTask.h"
#include "../lib/src/ledTask.h"
#include "../lib/src/displayTask.h"

QueueHandle_t inputQueue;
QueueHandle_t buzzQueue;
QueueHandle_t ledQueue;
QueueHandle_t displayQueue;
QueueHandle_t messageQueue;
hw_timer_t *interruptTimer = nullptr;
SemaphoreHandle_t interruptDisplaySemaphore;
SemaphoreHandle_t interruptLedSemaphore;
BaseType_t taskWoken = pdTRUE;

uint16_t divider = 80;
uint64_t timerMaxCount = 1000000;

void IRAM_ATTR onTimer() {
    xSemaphoreGiveFromISR(interruptDisplaySemaphore, &taskWoken);
    xSemaphoreGiveFromISR(interruptLedSemaphore, &taskWoken);
}

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println("---Device Control CLI---");
    Serial.println("Please enter a command, or type \"help\" for a list of them");

    inputQueue = xQueueCreate(3, sizeof(char) * 20);
    buzzQueue = xQueueCreate(3, sizeof(char) * 20);
    ledQueue = xQueueCreate(3, sizeof(char) * 20);
    displayQueue = xQueueCreate(3, sizeof(char) * 20);
    messageQueue = xQueueCreate(3, sizeof(char) * 20);
    interruptDisplaySemaphore = xSemaphoreCreateBinary();
    interruptLedSemaphore = xSemaphoreCreateBinary();

    xTaskCreate(
            cliInputTask,
            "CLI Input Task",
            1024,
            nullptr,
            1,
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

    xTaskCreate(
            ledTask,
            "LED Task",
            1024,
            nullptr,
            0,
            nullptr
    );

    xTaskCreate(
            displayTask,
            "Display Task",
            1300,
            nullptr,
            0,
            nullptr
    );

    interruptTimer = timerBegin(0, divider, true);
    timerAttachInterrupt(interruptTimer, &onTimer, true);
    timerAlarmWrite(interruptTimer, timerMaxCount, false);

}

void loop() {
    if (digitalRead(15) == LOW) {
        timerAlarmEnable(interruptTimer);
    }
}