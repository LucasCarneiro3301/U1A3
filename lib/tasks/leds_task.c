#include "tasks.h"

void vLEDTask(void *params)
{
    led_setup();    // Inicializa e configura os LEDs
    
    values_t values;

    while (true)
    {
        if (xQueueReceive(xQueueValues, &values, portMAX_DELAY) == pdTRUE) {
            gpio_put(GREEN, ((values.level < 7e3) && (values.vol < 8e3)));
            gpio_put(RED, !((values.level < 7e3) && (values.vol < 8e3)));
            printf("[Tarefa: %s] - LEVEL %u - VOL %u\n", pcTaskGetName(NULL), values.level, values.vol);
        }

        vTaskDelay(pdMS_TO_TICKS(50)); // Atualiza a cada 50ms
    }
}