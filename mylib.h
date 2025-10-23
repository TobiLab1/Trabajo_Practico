#ifndef MY_LIB
#define MY_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INICIO = 0,
    ESPERA,
    DISPENSA,
    ESPERA_RETIRO,
    SIN_STOCK,
    ERROR_ESTADO
} estados_t;

/* Configuración cargada desde config.conf */
typedef struct {
    int t_dispense;
    int t_cooldown;
    int t_check;
} config_t;

/* Prototipos */
config_t cargar_config(const char *path);

/* Funciones-estado: cada una recibe la config y devuelve el siguiente estado */
estados_t f_inicio(const config_t *cfg);
estados_t f_espera(const config_t *cfg);
estados_t f_dispensa(const config_t *cfg);
estados_t f_espera_retiro(const config_t *cfg);
estados_t f_sin_stock(const config_t *cfg);
estados_t f_error(const config_t *cfg);

#endif
