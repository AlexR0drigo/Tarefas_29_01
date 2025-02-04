#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LEDR_PIN 11 // Vermelho
#define LEDY_PIN 12 // Amarelo
#define LEDG_PIN 13 // Verde

// Estado do semáforo, representa qual a cor ele está atualmente
static volatile int state = 1; // inicializada como 1

// Callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de mudar o estado
    gpio_put(LEDR_PIN, 0);
    gpio_put(LEDY_PIN, 0);
    gpio_put(LEDG_PIN, 0);

    // Alterna o estado do semáforo
    switch (state) {
        case 1:
            gpio_put(LEDY_PIN, 1);
            state = 2;
            break;
        case 2:
            gpio_put(LEDG_PIN, 1);
            state = 3;
            break;
        case 3:
            gpio_put(LEDR_PIN, 1);
            state = 1;
            break;
    }
    return true;
}

int main() {
    stdio_init_all();

    // Inicializa os pinos dos LEDs
    gpio_init(LEDR_PIN);
    gpio_set_dir(LEDR_PIN, GPIO_OUT);
    gpio_init(LEDY_PIN);
    gpio_set_dir(LEDY_PIN, GPIO_OUT);
    gpio_init(LEDG_PIN);
    gpio_set_dir(LEDG_PIN, GPIO_OUT);

    // Liga o LED vermelho inicialmente
    gpio_put(LEDR_PIN, 1);

    // Configura o temporizador para alternar o semáforo a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    
    while (true) {
        // Mensagem que é exibida a cada 1 segundo, dizendo também qual cor está sendo exibida
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
