//
// Created by matt on 4/8/23.
//

#pragma once

void temperatureTask(void *parameter);

extern QueueHandle_t temperatureQueue;
extern QueueHandle_t humidityQueue;
