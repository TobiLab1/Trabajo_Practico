# Trabajo Practico

## Memoria descriptiva
El sistema desarrollado corresponde a un dispensador automático de alcohol en gel. Su funcionamiento comienza en un estado de inicialización, donde se cargan los parámetros de configuración (tiempo de dispensado, tiempos de espera y sensores).

Luego pasa al estado de espera, en el cual el sistema está listo para operar. Si se detecta una mano frente al sensor y hay suficiente alcohol disponible, la bomba se activa durante un tiempo definido para entregar una dosis.

Una vez finalizado el ciclo de dispensado, el sistema pasa a un estado de espera de retiro, donde se bloquea por un período breve para evitar que la misma detección de mano genere múltiples dosis consecutivas.

El dispensador además cuenta con un indicador visual de nivel mediante tres LEDs:

* Verde: nivel alto (funcionamiento normal).

* Amarillo: nivel bajo, pronto a agotarse.

* Rojo: nivel crítico o vacío (en este caso no se dispensa y se queda en estado de “sin stock” hasta recarga).

De esta forma, el sistema garantiza la entrega controlada y segura de alcohol en gel, evitando desperdicio y brindando información clara sobre el nivel disponible.

## Diagrama de estados

<img width="471" height="461" alt="Diagrama de estado drawio" src="https://github.com/user-attachments/assets/d7a6abe2-3215-4a74-8cd3-45adedecf7a5" />

