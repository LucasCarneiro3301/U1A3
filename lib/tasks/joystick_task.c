#include "tasks.h"

void vJoystickTask(void *params)
{
    adc_setup();
    
    values_t values;

    while (true)
    {
        adc_select_input(0);                    // GPIO 26 = ADC0
        values.level = (adc_read()*1e4)/4095;

        adc_select_input(1);                    // GPIO 27 = ADC1
        values.vol = (adc_read()*1e4)/4095;

        xQueueSend(xQueueValues, &values, 0);   // Envia o valor de nivel de agua e vol de chuva para a fila
        xQueueSend(xQueueValues, &values, 0);   // Envia o valor de nivel de agua e vol de chuva para a fila
        xQueueSend(xQueueValues, &values, 0);   // Envia o valor de nivel de agua e vol de chuva para a fila
        xQueueSend(xQueueValues, &values, 0);   // Envia o valor de nivel de agua e vol de chuva para a fila
        vTaskDelay(pdMS_TO_TICKS(100));         // 10 Hz de leitura
    }
}