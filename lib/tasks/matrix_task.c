#include "tasks.h"

void draw_water_level(float level_percent) {
    if (level_percent < 0) level_percent = 0;
    if (level_percent > 100) level_percent = 100;

    int full_rows = (int)(level_percent / 20.0f);
    float remainder = fmodf(level_percent, 20.0f);

    for (int row = 0; row < 5; row++) {
        int reversed_row = 4 - row;             // Topo é 0, base é 4
        float r = 0.0f, g = 0.0f, b = 0.0f;

        if (row < full_rows) {
            b = 0.045f;
        } else if (row == full_rows && remainder > 0.0f) {
            if (remainder > 15.0f)      b = 0.035f;
            else if (remainder > 10.0f) b = 0.025f;
            else if (remainder > 5.0f)  b = 0.015f;
            else if (remainder < 5.0f && remainder >= 1.0f ) b = 0.005f;
            else b = 0.0f;
        } else {
            b = 0.0f;
        }

        // Desenha da linha 0 (topo) até 4 (base)
        bool print_last = (row == 4);  // Só manda imprimir na última iteração
        ws2812_draw_row(r, g, b, reversed_row, false, print_last);
    }
}

void vMatrixTask(void *params) {
    ws2812_setup();     // Inicializa e configura a matriz de LEDs

    symbol('*');        // Apaga a matriz

    values_t values;

    while (true)
    {
        if (xQueueReceive(xQueueValues, &values, portMAX_DELAY) == pdTRUE) {
            if(show)    // Mostra o status do sistema
                symbol(((values.level < 7e3) && (values.vol < 8e3))?'v':'x');
            else        // Mostra o nível da água
            {
                draw_water_level((values.level)/100.0);
            }
            printf("[Tarefa: %s] - LEVEL %u - VOL %u\n", pcTaskGetName(NULL), values.level, values.vol);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}