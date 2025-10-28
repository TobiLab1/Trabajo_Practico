#include "mylib.h"
#include <stdio.h>

/* Simulación por entrada de usuario. */

int leer_sensor_presencia() {
    int valor;
    printf("Hay mano? (1 = si / 0 = no): ");
    scanf("%d", &valor);
    return valor;
}

int leer_nivel() {
    int valor;
    printf("Nivel de alcohol (0 = sin stock / 1 = bajo / 2 = alto): ");
    scanf("%d", &valor);
    return valor; // 0 = sin stock, 1 = bajo, 2 = alto (LEDs)
}

/*FUNCIONES DE ESTADO*/

estados_t f_inicio(const config_t *cfg) {
    printf("Tiempos cargados: dispense=%d ms, cooldown=%d ms, check=%d ms\n",
           cfg->t_dispense, cfg->t_cooldown, cfg->t_check);
    return ESPERA;
}

estados_t f_espera(const config_t *cfg) {
    printf("[ESPERA] Esperando mano...\n");
    int nivel = leer_nivel();

    if (nivel == 0) {
        printf("[ESPERA] Sin stock -> pasa a SIN_STOCK\n\n");
        return SIN_STOCK;
    }

    int presencia = leer_sensor_presencia();
    if (presencia && nivel > 0) {
        printf("[ESPERA] Mano detectada y nivel OK -> pasa a DISPENSA\n\n");
        return DISPENSA;
    }

    printf("[ESPERA] No hay mano. Se mantiene en ESPERA.\n\n");
    return ESPERA;
}

estados_t f_dispensa(const config_t *cfg) {
    printf("[DISPENSA] Dispensando alcohol durante %d ms...\n", cfg->t_dispense);
    printf("... (bomba activada) ...\n");

    int nivel = leer_nivel();
    if (nivel == 0) {
        printf("[DISPENSA] Sin stock detectado -> pasa a SIN_STOCK\n\n");
        return SIN_STOCK;
    }

    printf("[DISPENSA] Fin del ciclo -> pasa a ESPERA_RETIRO\n\n");
    return ESPERA_RETIRO;
}

estados_t f_espera_retiro(const config_t *cfg) {
    printf("[ESPERA_RETIRO] Esperando que se retire la mano (%d ms aprox.)\n", cfg->t_cooldown);
    printf("(simulación simple, presione Enter para continuar)\n");
    getchar(); getchar(); // para que el usuario apriete Enter

    int nivel = leer_nivel();
    if (nivel == 0) {
        printf("[ESPERA_RETIRO] Sin stock -> pasa a SIN_STOCK\n\n");
        return SIN_STOCK;
    }

    printf("[ESPERA_RETIRO] Cooldown terminado -> pasa a ESPERA\n\n");
    return ESPERA;
}

estados_t f_sin_stock(const config_t *cfg) {
    (void)cfg;
    printf("[SIN_STOCK] No hay alcohol. Reponer para continuar.\n");
    printf("Recargado? (1 = sí / 0 = no): ");
    int repuesto;
    scanf("%d", &repuesto);

    if (repuesto) {
        printf("[SIN_STOCK] Recarga detectada -> pasa a ESPERA\n\n");
        return ESPERA;
    } else {
        printf("[SIN_STOCK] Sigue sin stock -> se mantiene en SIN_STOCK\n\n");
        return SIN_STOCK;
    }
}

estados_t f_error(const config_t *cfg) {
    (void)cfg;
    printf("[ERROR] Error detectado. Reiniciar sistema.\n");
    printf("¿Reiniciar ahora? (1 = sí / 0 = no): ");
    int reset;
    scanf("%d", &reset);
    if (reset)
        return ESPERA;
    return ERROR_ESTADO;
}
