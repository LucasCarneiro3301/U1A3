#ifndef TASKS_H
#define TASKS_H

#include "../config/config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

typedef struct
{
    uint16_t vol;
    uint16_t level;
} values_t;

extern QueueHandle_t xQueueValues;

extern volatile bool show;

void vJoystickTask(void *params);
void vDisplayTask(void *params);
void vLEDTask(void *params);
void vBuzzerTask(void *params);
void vMatrixTask(void *params);

#endif