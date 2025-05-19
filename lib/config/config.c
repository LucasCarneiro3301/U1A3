#include "config.h"

void btn_setup() {
    gpio_init(BTNA);
    gpio_set_dir(BTNA, GPIO_IN);
    gpio_pull_up(BTNA);

    gpio_init(BTNB);
    gpio_set_dir(BTNB, GPIO_IN);
    gpio_pull_up(BTNB);
}

void led_setup() {
    gpio_init(GREEN);
    gpio_set_dir(GREEN, GPIO_OUT);
    gpio_put(GREEN, false);
    gpio_init(RED);
    gpio_set_dir(RED, GPIO_OUT);
    gpio_put(RED, false);
}

// Inicializa e configura a comunicação serial I2C 
void i2c_setup() {
    i2c_init(I2C_PORT, 4e2 * 1e3);              // Inicialização I2C.
  
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);  // Define a função do pino GPIO para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);  // Define a função do pino GPIO para I2C
    gpio_pull_up(I2C_SDA);                      // Pull up para linha de dados
    gpio_pull_up(I2C_SCL);                      // Pull up para linha de clock
}

// Limpa o display
void clear(ssd1306_t* ssd) {
    ssd1306_fill(ssd, false);
    ssd1306_send_data(ssd);
}

// Inicializa e configura o display
void ssd1306_setup(ssd1306_t* ssd) {
    ssd1306_init(ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); 
    ssd1306_config(ssd); 
    ssd1306_send_data(ssd);
    clear(ssd);
    ssd1306_send_data(ssd);
}

// Inicializa e configura a matriz de LEDs 5x5 
void ws2812_setup() {
    PIO pio = pio0;
    int sm = 0;

    uint offset = pio_add_program(pio, &ws2812_program);
  
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW); //Inicializa a matriz de leds
}

// Inicializa e configura os pinos do joystick como periféricos ADC
void adc_setup() {
    adc_gpio_init(JOY_Y);
    adc_gpio_init(JOY_X);
    adc_init();
}