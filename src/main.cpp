#include <Arduino.h>
#include </home/matt/CLionProjects/CLIProject/.pio/libdeps/esp32dev/U8g2/src/U8g2lib.h>
#include "../lib/src/cliInputTask.h"
#include "../lib/src/cliDispatcherTask.h"
#include "../lib/src/buzzTask.h"
#include "../lib/src/ledTask.h"
#include "../lib/src/displayTask.h"

QueueHandle_t inputQueue;
QueueHandle_t buzzQueue;
QueueHandle_t ledQueue;
QueueHandle_t displayQueue;
hw_timer_t *interruptTimer = nullptr;
SemaphoreHandle_t interruptSemaphore;
BaseType_t taskWoken = pdTRUE;

uint16_t divider = 80;
uint64_t timerMaxCount = 1000000;

void IRAM_ATTR onTimer() {
    xSemaphoreGiveFromISR(interruptSemaphore, &taskWoken);
}

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println("---Device Control CLI---");
    Serial.println("Please enter a command, or type \"help\" for a list of them");

    pinMode(33, OUTPUT); //Green
    pinMode(32, OUTPUT); // Yellow
    pinMode(27, OUTPUT); // Red
    pinMode(26, OUTPUT); // Blue
    inputQueue = xQueueCreate(3, sizeof(char) * 20);
    buzzQueue = xQueueCreate(3, sizeof(char) * 20);
    ledQueue = xQueueCreate(3, sizeof(char) * 20);
    displayQueue = xQueueCreate(3, sizeof(char) * 20);
    interruptSemaphore = xSemaphoreCreateBinary();

    pinMode(19, INPUT);
    digitalWrite(19, HIGH);

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

    /*
    xTaskCreate(
            buzzTask,
            "Buzz Task",
            1024,
            nullptr,
            0,
            nullptr
    );
*/
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
            1200,
            nullptr,
            0,
            nullptr
    );

    /*
    xTaskCreate(
            deferredInterruptTask,
            "Deferred Interrupt Task",
            1024,
            nullptr,
            5,
            nullptr
    );
    */

    interruptTimer = timerBegin(0, divider, true);
    timerAttachInterrupt(interruptTimer, &onTimer, true);
    timerAlarmWrite(interruptTimer, timerMaxCount, false);

}

void loop() {

}