#include "mylib.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* Helpers de simulación: preguntar al usuario por sensor y nivel.
   En la versión final estos leerían pines / ADC. */
static int leer_sensor_presencia(void) {
    char s[8];
    printf("Sim: mano presente? (s/n): ");
    if (!fgets(s, sizeof(s), stdin)) return 0;
    return (s[0] == 's' || s[0] == 'S');
}
static int leer_nivel_ok(void) {
    char s[8];
    printf("Sim: nivel OK? (s/n): ");
    if (!fgets(s, sizeof(s), stdin)) return 1; /* por defecto OK */
    return (s[0] == 's' || s[0] == 'S');
}

/* Retardo portable en ms */
static void wait_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep((useconds_t)ms * 1000);
#endif
}

/* INICIO: configura y pasa a ESPERA (no evalua condiciones) */
estados_t f_inicio(const config_t *cfg) {
    (void)cfg;
    printf("\n[INICIO] Inicializando sistema...\n");
    /* aquí se haría autotest, inicialización de GPIO, etc. */
    printf("[INICIO] Config completada -> pasando a ESPERA\n\n");
    return ESPERA;
}

/* ESPERA: si sensor && nivel_ok -> DISPENSA; si !nivel_ok -> SIN_STOCK;
   si no, se queda en ESPERA (autotransición) */
estados_t f_espera(const config_t *cfg) {
    (void)cfg;
    printf("[ESPERA] Esperando mano...\n");
    int nivel_ok = leer_nivel_ok();
    if (!nivel_ok) {
        printf("[ESPERA] Nivel NO OK -> SIN_STOCK\n\n");
        return SIN_STOCK;
    }

    int presencia = leer_sensor_presencia();
    if (presencia && nivel_ok) {
        printf("[ESPERA] Mano detectada y nivel OK -> DISPENSA\n\n");
        return DISPENSA;
    }

    /* queda en espera */
    printf("[ESPERA] Sin evento -> sigo en ESPERA\n\n");
    return ESPERA;
}

/* DISPENSA: activa la 'bomba' por t_dispense ms. Si durante el proceso nivel baja,
   se va a SIN_STOCK (simulado preguntando otra vez). */
estados_t f_dispensa(const config_t *cfg) {
    printf("[DISPENSA] Activando bomba por %d ms...\n", cfg->t_dispense);
    /* Simulamos dispensado con un sleep */
    wait_ms(cfg->t_dispense);

    /* chequeo nivel al finalizar (simulado) */
    printf("[DISPENSA] Fin dispensado. Chequeando nivel...\n");
    int nivel_ok = leer_nivel_ok();
    if (!nivel_ok) {
        printf("[DISPENSA] Nivel NO OK -> SIN_STOCK\n\n");
        return SIN_STOCK;
    }

    printf("[DISPENSA] Dispensa completa -> ESPERA_RETIRO (cooldown)\n\n");
    return ESPERA_RETIRO;
}

/* ESPERA_RETIRO: espera el cooldown evitando re-dispensar inmediatamente.
   Luego vuelve a ESPERA (o a SIN_STOCK si no hay nivel). */
estados_t f_espera_retiro(const config_t *cfg) {
    printf("[ESPERA_RETIRO] Esperando cooldown %d ms...\n", cfg->t_cooldown);
    wait_ms(cfg->t_cooldown);

    int nivel_ok = leer_nivel_ok();
    if (!nivel_ok) {
        printf("[ESPERA_RETIRO] Nivel NO OK -> SIN_STOCK\n\n");
        return SIN_STOCK;
    }

    printf("[ESPERA_RETIRO] Cooldown terminado -> ESPERA\n\n");
    return ESPERA;
}

/* SIN_STOCK: se queda en este estado hasta que se indique recarga (simulado por entrada) */
estados_t f_sin_stock(const config_t *cfg) {
    (void)cfg;
    printf("[SIN_STOCK] SIN STOCK. No dispensar. Esperando recarga (s) o seguir sin stock (n).\n");
    char s[8];
    if (!fgets(s, sizeof(s), stdin)) return SIN_STOCK;
    if (s[0] == 's' || s[0] == 'S') {
        printf("[SIN_STOCK] Recarga confirmada -> ESPERA\n\n");
        return ESPERA;
    }
    printf("[SIN_STOCK] Seguir sin stock -> me mantengo en SIN_STOCK\n\n");
    return SIN_STOCK;
}

/* ERROR: placeholder */
estados_t f_error(const config_t *cfg) {
    (void)cfg;
    printf("[ERROR] Estado de error. Requiere intervención (reset manual).\n");
    /* En este modo de aprendizaje volvemos a ESPERA si el usuario presiona s */
    char s[8];
    printf("¿Resetear? (s/n): ");
    if (!fgets(s, sizeof(s), stdin)) return ERROR_ESTADO;
    if (s[0] == 's' || s[0] == 'S') return ESPERA;
    return ERROR_ESTADO;
}
