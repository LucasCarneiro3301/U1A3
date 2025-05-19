#include "tasks.h"

// Frequências das notas musicais (em Hz)
enum Notes {
    DO = 2640, // Dó
    RE = 2970, // Ré
    MI = 3300, // Mi
    FA = 3520, // Fá
    SOL = 3960, // Sol
    LA = 4400, // Lá
    SI = 4950,  // Si
    DO_ALTO = 5280,  // Dó uma oitava acima (C5)
    LA_BAIXO = 880
};

// Configura o PWM no pino do buzzer com uma frequência especificada
void set_buzzer_frequency(uint frequency) {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(BUZZER, 0);
}

// Função para tocar o buzzer por um tempo especificado (em milissegundos)
void play_buzzer(uint frequency) {
    set_buzzer_frequency(frequency);
    pwm_set_gpio_level(BUZZER, 32768);
}

void stop_buzzer() {
    pwm_set_gpio_level(BUZZER, 0);
}

void jingle() {
    for (int i = 0; i < 3; i++) {
        play_buzzer(RE);
        vTaskDelay(pdMS_TO_TICKS(150));
        
        stop_buzzer();
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    stop_buzzer();
    vTaskDelay(pdMS_TO_TICKS(1400));
}

void vBuzzerTask(void *params) 
{
    values_t values;
    bool in_alert = false;

    values.level = 0;
    values.vol = 0;

    while (true)
    {
        values_t new_values;
        if (xQueueReceive(xQueueValues, &new_values, portMAX_DELAY) == pdTRUE) {
            values = new_values;
            printf("[Tarefa: %s] - LEVEL %u - VOL %u\n", pcTaskGetName(NULL), values.level, values.vol);
        }

        in_alert = !((values.level < 7e3) && (values.vol < 8e3));

        if (in_alert) {
            jingle();
        } else {
            stop_buzzer();
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}