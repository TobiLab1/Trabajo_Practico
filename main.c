#include "mylib.h"

int main(void) {
    init_driver();
    estados_t estado = INICIO;

    while (1) {
        switch (estado) {
            case INICIO: estado = f_inicio(&cfg); 
            break;
            case ESPERA: estado = f_espera(&cfg); 
            break;
            case DISPENSA: estado = f_dispensa(&cfg); 
            break;
            case ESPERA_RETIRO: estado = f_espera_retiro(&cfg); 
            break;
            case SIN_STOCK: estado = f_sin_stock(&cfg); 
            break;
            default: estado = INICIO; 
            break;
        }
    }
    return 0;
}
