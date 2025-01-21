//
// Created by matt on 4/7/23.
//

#pragma once

void displayTask(void *parameter);
extern QueueHandle_t displayQueue;
extern SemaphoreHandle_t interruptDisplaySemaphore;
