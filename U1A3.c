#include "config/config.h"
#include "tasks/tasks.h"

QueueHandle_t xQueueValues;

volatile uint32_t last_time = 0;        // Armazena o tempo do último evento (em microssegundos)
volatile bool show = true;              // Controla o que aparece na matriz

void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();
    btn_setup();

    gpio_set_irq_enabled_with_callback(BTNB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);  // Callback para BTNB
    gpio_set_irq_enabled_with_callback(BTNA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);  // Callback para BTNA

    xQueueValues = xQueueCreate(10, sizeof(values_t));  // Cria a fila para compartilhamento dos valores de nível e volume

    xTaskCreate(vJoystickTask, "Joystick Task", 256, NULL, 1, NULL);    // Task do joystick
    xTaskCreate(vDisplayTask, "Display Task", 512, NULL, 1, NULL);      // Task do display  
    xTaskCreate(vLEDTask, "LED Task", 256, NULL, 1, NULL);              // Task dos LEDs
    xTaskCreate(vBuzzerTask, "Buzzer Task", 256, NULL, 1, NULL);        // Task do buzzer
    xTaskCreate(vMatrixTask, "Matrix Task", 256, NULL, 1, NULL);        // Task da matriz de LEDs
    
    // Inicia o agendador
    vTaskStartScheduler();
    panic_unsupported();
}


// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());  // Obtém o tempo atual em microssegundos
  
    if (current_time - last_time > 2e5) {   // 200 ms de debouncing
        last_time = current_time; 
        if(gpio == BTNA) {
            show = !show;   // Alterna a visualização da matriz
        } else if(gpio == BTNB) {
            reset_usb_boot(0, 0);
        }
    }
}