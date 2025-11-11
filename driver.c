#include "mylib.h"
#include "avr_api.h"

void init_driver(void) {
    // Configura los LEDs como salida
    GpioInitStructure_AVR leds;
    leds.port = avr_GPIO_A;
    leds.modo = avr_GPIO_mode_Output;
    leds.pines = avr_GPIO_PIN_0 | avr_GPIO_PIN_1 | avr_GPIO_PIN_2; // A0, A1, A2
    init_gpio(leds);

    // Configura el sensor IR como entrada
    GpioInitStructure_AVR sensor;
    sensor.port = avr_GPIO_B;
    sensor.modo = avr_GPIO_mode_Input;
    sensor.pines = avr_GPIO_PIN_0;
    init_gpio(sensor);

    // Configura la bomba como salida
    GpioInitStructure_AVR bomba;
    bomba.port = avr_GPIO_B;
    bomba.modo = avr_GPIO_mode_Output;
    bomba.pines = avr_GPIO_PIN_1;
    init_gpio(bomba);
}

// LEDs
void driver_led_verde_on(void)    { set_pin(avr_GPIO_A, 0); }
void driver_led_verde_off(void)   { clear_pin(avr_GPIO_A, 0); }

void driver_led_amarillo_on(void) { set_pin(avr_GPIO_A, 1); }
void driver_led_amarillo_off(void){ clear_pin(avr_GPIO_A, 1); }

void driver_led_rojo_on(void)     { set_pin(avr_GPIO_A, 2); }
void driver_led_rojo_off(void)    { clear_pin(avr_GPIO_A, 2); }

// Sensor de mano
int driver_mano_detectada(void) {
    return avr_GPIOB_IN_0;
}

// Sensor de nivel
int driver_nivel_ok(void) {
    // Devuelve 1 (nivel correcto)
    return 1;
}

// Bomba
void driver_bomba_on(void)  { set_pin(avr_GPIO_B, 1); }
void driver_bomba_off(void) { clear_pin(avr_GPIO_B, 1); }

// Delay
void driver_delay_ms(unsigned int ms) {
    // Delay aproximado
    volatile unsigned int i;
    for (i = 0; i < ms * 100; i++);
}
