#include "mylib.h"

config_t cargar_config(const char *path) {
    config_t cfg;
    /* valores por defecto*/
    cfg.t_dispense = 600;
    cfg.t_cooldown = 3000;
    cfg.t_check = 80;

    FILE *f = fopen(path, "r");
    if (!f) {
        printf("[config] No se encontro %s. Usando valores por defecto.\n", path);
        return cfg;
    }

    char key[64];
    int value;
    while (fscanf(f, "%63s %d", key, &value) == 2) {
        if (strcmp(key, "t_dispense") == 0) cfg.t_dispense = value;
        else if (strcmp(key, "t_cooldown") == 0) cfg.t_cooldown = value;
        else if (strcmp(key, "t_check") == 0) cfg.t_check = value;
    }
    fclose(f);
    printf("[config] Cargada: t_dispense=%d ms, t_cooldown=%d ms, t_check=%d ms\n",
           cfg.t_dispense, cfg.t_cooldown, cfg.t_check);
    return cfg;
}
