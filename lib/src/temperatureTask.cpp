//
// Created by matt on 4/8/23.
//

#include <Arduino.h>
#include "temperatureTask.h"
#include </home/matt/CLionProjects/CLIProject/.pio/libdeps/esp32dev/DHT sensor library/DHT.h>

//Constants for initializing the DHT sensor
#define dhtPin 19
#define dhtType DHT11

//DHT sensor initialization
DHT dht(dhtPin, dhtType);

//Task that starts the DHT sensor and takes readings every quarter second
void temperatureTask(void *parameter) {
    dht.begin();
    //Non-blocking delay that allows the sensor to load
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    //Buffers for temperature and humidity
    char temperatureBuffer[20];
    char humidityBuffer[20];

    while (1) {
        vTaskDelay(250 / portTICK_PERIOD_MS);
        //Floats that read and hold temperature and humidity values
        float t = dht.readTemperature(true);
        float h = dht.readHumidity();

        //Converts the float temperature and humidity values to a string (so u8g2 can properly display them)
        //and then sends the converted values to the appropriate queue
        dtostrf(t, 5, 2, temperatureBuffer);
        xQueueSend(temperatureQueue, temperatureBuffer, 0);
        dtostrf(h, 5, 2, humidityBuffer);
        xQueueSend(humidityQueue, humidityBuffer, 0);
    }
}


