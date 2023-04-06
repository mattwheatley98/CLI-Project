#include <Arduino.h>
#include "../lib/src/cliInputTask.h"
#include "../lib/src/cliDispatcherTask.h"

QueueHandle_t inputQueue;

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println("---Device Control CLI---");
    Serial.println("Please enter a command, or type \"help\" for a list of them");

    inputQueue = xQueueCreate(5, sizeof(char) * 20);

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
            1,
            nullptr
    );
}

void loop() {

}