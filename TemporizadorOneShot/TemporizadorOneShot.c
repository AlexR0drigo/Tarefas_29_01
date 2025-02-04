#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define LEDB_PIN 11 // Led azul 
#define LEDR_PIN 12 // Led Vermelho
#define LEDG_PIN 13 // Led Verde
#define BUTTON_0 5

static volatile uint32_t last_time = 0;
bool led_ativo = false;
uint8_t nivel_led = 0;

// Callback para alterar o estado dos LEDs
int64_t led_sequence_callback(alarm_id_t id, void *user_data) {
    switch (nivel_led) {
        case 1:
            gpio_put(LEDB_PIN, 0); // Desliga LED Azul
            break;
        case 2:
            gpio_put(LEDR_PIN, 0); // Desliga LED Vermelho
            break;
        case 3:
            gpio_put(LEDG_PIN, 0); // Desliga LED Verde
            led_ativo = false; // Permite reiniciar o ciclo
            return 0;
    }
    nivel_led++;
    add_alarm_in_ms(3000, led_sequence_callback, NULL, false);
    return 0;
}

static void gpio_irq_handler(uint gpio, uint32_t events);

int main() {
    stdio_init_all();
    
    gpio_init(LEDB_PIN);
    gpio_set_dir(LEDB_PIN, GPIO_OUT);
    gpio_put(LEDB_PIN, 0); // Inicializa desligado

    gpio_init(LEDR_PIN);
    gpio_set_dir(LEDR_PIN, GPIO_OUT);
    gpio_put(LEDR_PIN, 0); // Inicializa desligado

    gpio_init(LEDG_PIN);
    gpio_set_dir(LEDG_PIN, GPIO_OUT);
    gpio_put(LEDG_PIN, 0); // Inicializa desligado
    
    gpio_init(BUTTON_0);
    gpio_set_dir(BUTTON_0, GPIO_IN);
    gpio_pull_up(BUTTON_0);

    gpio_set_irq_enabled_with_callback(BUTTON_0, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    
    while (true) {
        sleep_ms(100);
    }
    return 0;
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento (debouncing)
    if (current_time - last_time > 200000) { // 200ms de debounce
        last_time = current_time;

        if (gpio_get(BUTTON_0) == 0 && !led_ativo) {
            led_ativo = true;
            nivel_led = 1;
            
            // Liga todos os LEDs
            gpio_put(LEDB_PIN, 1);
            gpio_put(LEDR_PIN, 1);
            gpio_put(LEDG_PIN, 1);

            // Inicia a sequência de desligamento
            add_alarm_in_ms(3000, led_sequence_callback, NULL, false);
        }
    }
}
