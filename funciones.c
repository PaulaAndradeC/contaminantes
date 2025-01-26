#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Definir los nombres de los contaminantes aquí, solo en funciones.c
const char *NOMBRE_CONTAMINANTES[NUM_CONTAMINANTES] = {"CO2", "SO2", "NO2", "PM2.5"};
const float LIMITES_OMS[NUM_CONTAMINANTES] = {50, 40, 25, 15}; // Límites OMS para CO2, SO2, NO2 y PM2.

void ingresar_datos_actuales(Zona zonas[NUM_ZONAS]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Ingrese los datos actuales para Zona %d:\n", i+1);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            printf("Nivel de %s: ", NOMBRE_CONTAMINANTES[j]);
            while (1) {
                scanf("%f", &zonas[i].niveles_contaminantes[j]);
                if (zonas[i].niveles_contaminantes[j] < 0) {
                    printf("Error al leer el nivel de %s para Zona %d. Ingrese un valor valido (positivo).\n", NOMBRE_CONTAMINANTES[j], i+1);
                } else {
                    break;
                }
            }
        }
        printf("Temperatura: ");
        while (1) {
            scanf("%f", &zonas[i].temperatura);
            if (zonas[i].temperatura < -100 || zonas[i].temperatura > 60) {
                printf("Error al leer la temperatura para Zona %d. Ingrese un valor valido.\n", i+1);
            } else {
                break;
            }
        }
        
        printf("Velocidad del viento: ");
        while (1) {
            scanf("%f", &zonas[i].velocidad_viento);
            if (zonas[i].velocidad_viento < 0) {
                printf("Error al leer la velocidad del viento para Zona %d. Ingrese un valor valido (positivo).\n", i+1);
            } else {
                break;
            }
        }

        printf("Humedad: ");
        while (1) {
            scanf("%f", &zonas[i].humedad);
            if (zonas[i].humedad < 0 || zonas[i].humedad > 100) {
                printf("Error al leer la humedad para Zona %d. Ingrese un valor valido (0-100).\n", i+1);
            } else {
                break;
            }
        }
    }
}

void calcular_niveles_contaminacion_actual(Zona zonas[NUM_ZONAS]) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("\nCalculando los niveles actuales de contaminacion para Zona %d:\n", i + 1);

        // Calculamos los niveles de contaminación en base a los datos actuales
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            // Ejemplo de cálculo simple, puedes usar diferentes fórmulas según tus necesidades
            float nivel_base = zonas[i].niveles_contaminantes[j];
            float temperatura = zonas[i].temperatura;
            float velocidad_viento = zonas[i].velocidad_viento;
            float humedad = zonas[i].humedad;

            // Suposición de un cálculo simple, por ejemplo, ajustamos el nivel de contaminación según la temperatura y otros factores
            float nivel_ajustado = nivel_base * (1 + (temperatura * 0.02)) * (1 + (velocidad_viento * 0.01)) * (1 + (humedad * 0.005));

            // Guardamos el resultado ajustado en el mismo array de niveles de contaminación
            zonas[i].niveles_contaminantes[j] = nivel_ajustado;

            // Mostrar el nivel ajustado
            printf("%s: %.2f (ajustado)\n", NOMBRE_CONTAMINANTES[j], zonas[i].niveles_contaminantes[j]);
        }
    }
}

void calcular_predicciones(Zona zonas[NUM_ZONAS]) {
    printf("Calculando predicciones basadas en los datos actuales...\n");
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Zona %d:\n", i+1);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            printf("Prediccion para %s: %.2f\n", NOMBRE_CONTAMINANTES[j], zonas[i].niveles_contaminantes[j] * 1.1); // Aumento del 10% para simular predicción
        }
        printf("Prediccion para temperatura: %.2f\n", zonas[i].temperatura + 1.5); // Aumento de temperatura para la predicción
        printf("Prediccion para velocidad del viento: %.2f\n", zonas[i].velocidad_viento * 1.2); // Aumento en la velocidad del viento
        printf("Prediccion para humedad: %.2f\n", zonas[i].humedad * 1.05); // Aumento de humedad para la predicción
    }
}

void mostrar_comparacion_oms(Zona zonas[NUM_ZONAS]) {
    printf("Comparando los niveles de contaminantes con los limites de la OMS:\n");
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Zona %d:\n", i+1);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            printf("%s: %.2f - ", NOMBRE_CONTAMINANTES[j], zonas[i].niveles_contaminantes[j]);
            if (zonas[i].niveles_contaminantes[j] > LIMITES_OMS[j]) {
                printf("Supera el limite OMS\n");
            } else {
                printf("Dentro del limite OMS\n");
            }
        }
    }
}

void generar_alertas_y_recomendaciones(Zona zonas[NUM_ZONAS]) {
    printf("Generando alertas y recomendaciones:\n");
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Zona %d:\n", i+1);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            if (zonas[i].niveles_contaminantes[j] > LIMITES_OMS[j]) {
                printf("ALERTA: %s en Zona %d supera el limite OMS. Recomendacion: Reducir la contaminacion.\n", NOMBRE_CONTAMINANTES[j], i+1);
            } else {
                printf("Recomendacion: Mantener los niveles de %s en Zona %d dentro del limite OMS.\n", NOMBRE_CONTAMINANTES[j], i+1);
            }
        }
    }
}

void calcular_promedios_historicos(Zona zonas[NUM_ZONAS]) {
    printf("Calculando promedios historicos de contaminacion...\n");
    for (int i = 0; i < NUM_ZONAS; i++) {
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            float suma = 0;
            for (int d = 0; d < NUM_DIAS_HISTORICOS; d++) {
                suma += zonas[i].historial_contaminacion[d][j];
            }
            float promedio = suma / NUM_DIAS_HISTORICOS;
            printf("Promedio historico de %s en Zona %d: %.2f\n", NOMBRE_CONTAMINANTES[j], i+1, promedio);
        }
    }
}

void exportar_datos(Zona zonas[NUM_ZONAS]) {
    FILE *archivo = fopen("reporte_contaminacion.txt", "w");
    if (!archivo) {
        printf("Error al abrir el archivo para exportar datos.\n");
        return;
    }
    fprintf(archivo, "Reporte de contaminacion\n\n");
    for (int i = 0; i < NUM_ZONAS; i++) {
        fprintf(archivo, "Zona %d:\n", i+1);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            fprintf(archivo, "%s: %.2f\n", NOMBRE_CONTAMINANTES[j], zonas[i].niveles_contaminantes[j]);
        }
        fprintf(archivo, "Temperatura: %.2f\n", zonas[i].temperatura);
        fprintf(archivo, "Velocidad del viento: %.2f\n", zonas[i].velocidad_viento);
        fprintf(archivo, "Humedad: %.2f\n", zonas[i].humedad);
    }
    fclose(archivo);
   // printf("Datos exportados exitosamente a 'reporte_contaminacion.txt'.\n");
}
