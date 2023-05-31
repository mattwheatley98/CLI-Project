#include <Arduino.h>
#include "../lib/src/cliInputTask.h"
#include "../lib/src/ledTask.h"
#include "../lib/src/displayTask.h"
#include "../lib/src/temperatureTask.h"

//Queue handles
QueueHandle_t inputQueue;
QueueHandle_t ledQueue;
QueueHandle_t displayQueue;
QueueHandle_t temperatureQueue;
QueueHandle_t humidityQueue;

//ISR-related handles and constants
hw_timer_t *interruptTimer;
SemaphoreHandle_t interruptDisplaySemaphore;
SemaphoreHandle_t interruptLedSemaphore;
BaseType_t taskWoken = pdTRUE;
const uint16_t divider = 80;
const uint64_t timerMaxCount = 1000000;

//ISR callback function (stored on RAM) that defers work to the display and LED tasks
void IRAM_ATTR onTimer() {
    xSemaphoreGiveFromISR(interruptDisplaySemaphore, &taskWoken);
    xSemaphoreGiveFromISR(interruptLedSemaphore, &taskWoken);
}

void setup() {
    //Start serial monitor and print welcome message
    Serial.begin(9600);
    Serial.println();
    Serial.println("---Device Control CLI---");
    Serial.println("Please enter a command, or type \"help\" for a list of them");

    //Queue initialization
    inputQueue = xQueueCreate(3, sizeof(char) * 20);
    ledQueue = xQueueCreate(3, sizeof(char) * 20);
    displayQueue = xQueueCreate(3, sizeof(char) * 20);
    temperatureQueue = xQueueCreate(3, sizeof(char) * 20);
    humidityQueue = xQueueCreate(3, sizeof(char) * 20);

    //Semaphore initialization
    interruptDisplaySemaphore = xSemaphoreCreateBinary();
    interruptLedSemaphore = xSemaphoreCreateBinary();

    //Initialize CLI Input Task
    xTaskCreate(
            cliInputTask,
            "CLI Input Task",
            1024,
            nullptr,
            1,
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
            1400,
            nullptr,
            0,
            nullptr
    );

    xTaskCreate(
            temperatureTask,
            "Temperature Task",
            1400,
            nullptr,
            0,
            nullptr
    );

    //ISR-related functions
    interruptTimer = timerBegin(0, divider, true);
    timerAttachInterrupt(interruptTimer, &onTimer, true);
    timerAlarmWrite(interruptTimer, timerMaxCount, false);

}

//Loop that triggers the ISR when the shock sensor is triggered
void loop() {
    if (digitalRead(15) == LOW) {
        timerAlarmEnable(interruptTimer);
    }
}