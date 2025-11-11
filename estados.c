#include "mylib.h"
#include <stdio.h>

// Estado de inicio: inicializa sistema y enciende LED verde
estados_t f_inicio(void) {
    driver_led_verde_on();
    driver_led_amarillo_off();
    driver_led_rojo_off();
    return ESPERA;
}

// Estado de espera: aguarda detección de mano o falta de stock
estados_t f_espera(void) {
    if (!driver_nivel_ok()) {
        driver_led_verde_off();
        driver_led_rojo_on();
        return SIN_STOCK;
    }

    if (driver_mano_detectada()) {
        driver_led_verde_off();
        driver_led_amarillo_on();
        return DISPENSA;
    }

    return ESPERA;
}

// Estado de dispensado: activa bomba durante un tiempo determinado
estados_t f_dispensa(void) {
    driver_led_amarillo_on();
    driver_bomba_on();
    driver_delay_ms(600);   // tiempo de dispensado
    driver_bomba_off();
    driver_led_amarillo_off();
    return ESPERA_RETIRO;
}

// Espera que la mano se retire antes de volver al estado de espera
estados_t f_espera_retiro(void) {
    driver_delay_ms(1500);  // tiempo de cooldown
    driver_led_verde_on();
    return ESPERA;
}

// Estado sin stock: espera hasta que se recargue el tanque
estados_t f_sin_stock(void) {
    driver_led_rojo_on();
    while (!driver_nivel_ok());
    driver_led_rojo_off();
    driver_led_verde_on();
    return ESPERA;
}
