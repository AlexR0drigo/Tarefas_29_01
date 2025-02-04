#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

// Estado do semáforo
static volatile int state = 1;

// Callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de mudar o estado
    gpio_put(LED_RED, 0);
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_GREEN, 0);

    // Alterna o estado do semáforo
    switch (state) {
        case 1:
            gpio_put(LED_YELLOW, 1);
            state = 2;
            break;
        case 2:
            gpio_put(LED_GREEN, 1);
            state = 3;
            break;
        case 3:
            gpio_put(LED_RED, 1);
            state = 1;
            break;
    }
    return true;
}

int main() {
    stdio_init_all();

    // Inicializa os pinos dos LEDs
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Liga o LED vermelho inicialmente
    gpio_put(LED_RED, 1);

    // Configura o temporizador para alternar o semáforo a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {

        switch (state) {
            case 1:
                printf("Semáforo operando na cor vermelha...\n");
                sleep_ms(1000);
                break;
            case 2:
                printf("Semáforo operando na cor amarela...\n");
                sleep_ms(1000);
                break;
            case 3:
                printf("Semáforo operando na cor verde...\n");
                sleep_ms(1000);
                break;
        }
    }
    return 0;
}
