#include <stdio.h>
#include "funciones.h"

int main() {
    Zona zonas[NUM_ZONAS] = {0}; // Inicializar todas las zonas

    int opcion;
    do {
        printf("\nMenu de Opciones:\n");
        printf("1. Ingresar datos actuales\n");
        printf("2. Calcular niveles actuales de contaminacion\n");
        printf("3. Mostrar comparacion con limites OMS\n");
        printf("4. Generar alertas y recomendaciones\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresar_datos_actuales(zonas);
                break;
            case 2:
                calcular_niveles_contaminacion_actual(zonas);
                break;
            case 3:
                mostrar_comparacion_oms(zonas);
                break;
            case 4:
                generar_alertas_y_recomendaciones(zonas);
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}
