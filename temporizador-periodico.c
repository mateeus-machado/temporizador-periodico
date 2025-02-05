#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define LED_VERMELHO 13
#define LED_AMARELO 12
#define LED_VERDE 11

int estado = 0; // Estado inicial do semáforo

// Função de callback do temporizador para alternar os estados do semáforo
bool alternar_semaforo(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de acender o próximo
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Alterna o estado do semáforo
    switch (estado) {
        case 0:
            gpio_put(LED_VERMELHO, 1);
            estado = 1;
            break;
        case 1:
            gpio_put(LED_AMARELO, 1);
            estado = 2;
            break;
        case 2:
            gpio_put(LED_VERDE, 1);
            estado = 0;
            break;
    }
    return true;
}

int main() {
    stdio_init_all();

    // Configuração dos pinos como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Inicializa o temporizador para alternar o semáforo a cada 3 segundos
    struct repeating_timer temporizador;
    add_repeating_timer_ms(3000, alternar_semaforo, NULL, &temporizador);

    // Loop principal
    while (true) {
        printf("Semáforo em execução...\n");
        sleep_ms(1000);
    }

    return 0;
}
