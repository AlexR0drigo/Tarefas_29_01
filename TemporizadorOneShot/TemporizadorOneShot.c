#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define LEDB_PIN 11 // Led azul 
#define LEDR_PIN 12 // Led Vermelho
#define LEDG_PIN 13 // Led Verde
#define button_0 5

static volatile uint32_t last_time = 0;
bool leds_active = false;
uint8_t led_stage = 0;

// Callback para alterar o estado dos LEDs
int64_t led_sequence_callback(alarm_id_t id, void *user_data) {
    switch (led_stage) {
        case 1:
            gpio_put(LEDB_PIN, false);
            break;
        case 2:
            gpio_put(LEDR_PIN, false);
            break;
        case 3:
            gpio_put(LEDG_PIN, false);
            leds_active = false; // Permite reiniciar o ciclo
            return 0;
    }
    led_stage++;
    add_alarm_in_ms(3000, led_sequence_callback, NULL, false);
    return 0;
}

static void gpio_irq_handler(uint gpio, uint32_t events);

int main() {
    stdio_init_all();
    
    gpio_init(LEDB_PIN);
    gpio_set_dir(LEDB_PIN, GPIO_OUT);
    gpio_init(LEDR_PIN);
    gpio_set_dir(LEDR_PIN, GPIO_OUT);
    gpio_init(LEDG_PIN);
    gpio_set_dir(LEDG_PIN, GPIO_OUT);
    
    gpio_init(button_0);
    gpio_set_dir(button_0, GPIO_IN);
    gpio_pull_up(button_0);

    gpio_set_irq_enabled_with_callback(button_0, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    
    while (true) {
        
    }
    return 0;
}

void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento (debouncing)
    if (current_time - last_time > 200000) // 200ms de debouncing
    {
        last_time = current_time; // atualiza o tempo

        if (gpio_get(button_0) == 0 && !leds_active) {

                leds_active = true;
                led_stage = 1;
                gpio_put(LEDB_PIN, true);
                gpio_put(LEDR_PIN, true);
                gpio_put(LEDG_PIN, true);
                add_alarm_in_ms(3000, led_sequence_callback, NULL, false);
            }
     
        
    }
}