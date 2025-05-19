#include "tasks.h"

void vDisplayTask(void *params)
{
    i2c_setup();            // Inicializa e configura a comunicação I2C

    ssd1306_t ssd;
    ssd1306_setup(&ssd);    // Inicializa e configura o display

    values_t values;
    bool cor = true, mode;
    char str[16];

    while (true)
    {
        if (xQueueReceive(xQueueValues, &values, portMAX_DELAY) == pdTRUE) {
            ssd1306_fill(&ssd, !cor);                           // Limpa o display
            ssd1306_rect(&ssd, 1, 1, 123, 63, cor, !cor);       // Retângulo da área útil
            sprintf(str, "LEVEL:%.2f%%", (values.level)/100.0);
            ssd1306_draw_string(&ssd, str ,4, 4);
            sprintf(str, "VOL:%.2f%%", (values.vol)/100.0);
            ssd1306_draw_string(&ssd, str,4, 20);
            ssd1306_draw_string(&ssd, ((values.level < 7e3) && (values.vol < 8e3)) ? "MODE:NORMAL" : "MODE:ALERT",4, 47);
            ssd1306_line(&ssd, 1, 36, 123, 36, cor);		    // Desenha uma linha
            ssd1306_send_data(&ssd);                            // Atualiza o display
            printf("[Tarefa: %s] - LEVEL %u - VOL %u\n", pcTaskGetName(NULL), values.level, values.vol);
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Atualiza a cada 50ms
    }
}