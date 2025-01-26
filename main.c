#include <stdio.h>
#include "funciones.h"

int main() {
    Zona zonas[NUM_ZONAS];
    cargar_datos(zonas, "datos.dat");

    ejecutar_menu(zonas);

    guardar_datos(zonas, "datos.dat");

    return 0;
}
