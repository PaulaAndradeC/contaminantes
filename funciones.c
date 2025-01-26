#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const float LIMITES_OMS[NUM_CONTAMINANTES] = {50, 40, 25, 15};
const char *NOMBRE_CONTAMINANTES[NUM_CONTAMINANTES] = {"CO2", "SO2", "NO2", "PM2.5"};

float promedio_ponderado(const float *valores, int n, int *error) {
    if (valores == NULL || n <= 0) {
        if (error) *error = 1;
        return NAN;
    }
    float suma_ponderada = 0;
    float suma_pesos = 0;
    for (int i = 0; i < n; i++) {
        float peso = (float)(n - i) / n;
        suma_ponderada += valores[i] * peso;
        suma_pesos += peso;
    }
    if (error) *error = 0;
    return suma_ponderada / suma_pesos;
}

int guardar_datos(const Zona *zonas, const char *nombre_archivo) {
    if (zonas == NULL || nombre_archivo == NULL) return 1;
    FILE *archivo = fopen(nombre_archivo, "wb");
    if (archivo == NULL) return 1;
    size_t elementos_escritos = fwrite(zonas, sizeof(Zona), NUM_ZONAS, archivo);
    fclose(archivo);
    return (elementos_escritos != NUM_ZONAS);
}

int cargar_datos(Zona *zonas, const char *nombre_archivo) {
    if (zonas == NULL || nombre_archivo == NULL) return 1;
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (archivo == NULL) {
        for (int i = 0; i < NUM_ZONAS; i++) {
            snprintf(zonas[i].nombre, 50, "Zona %d", i + 1);
        }
        return 0;
    }
    size_t elementos_leidos = fread(zonas, sizeof(Zona), NUM_ZONAS, archivo);
    fclose(archivo);
    if (elementos_leidos != NUM_ZONAS && !feof(archivo)) return 1;
    return 0;
}

void simular_datos_historicos(Zona *zonas) {
    if (zonas == NULL) return;
    for (int i = 0; i < NUM_ZONAS; i++) {
        for (int d = 0; d < DIAS_HISTORICOS; d++) {
            for (int j = 0; j < NUM_CONTAMINANTES; j++) {
                zonas[i].historico[d].niveles[j] = (float)rand() / RAND_MAX * 100;
            }
        }
    }
}

int ingresar_datos_actuales(Zona *zonas) {
    if (zonas == NULL) return 1;
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Ingrese los datos actuales para %s:\n", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            while (1) {
                printf("Nivel de %s: ", NOMBRE_CONTAMINANTES[j]);
                if (scanf("%f", &zonas[i].actual.niveles[j]) != 1 || zonas[i].actual.niveles[j] < 0) {
                    fprintf(stderr, "Error al leer el nivel de %s para %s. Ingrese un valor valido (positivo).\n", NOMBRE_CONTAMINANTES[j], zonas[i].nombre);
                    while(getchar() != '\n');
                } else {
                    break;
                }
            }
        }

        while (1) {
            printf("Temperatura: ");
            if (scanf("%f", &zonas[i].actual.temperatura) != 1) {
                fprintf(stderr, "Error al leer la temperatura para %s. Ingrese un valor valido.\n", zonas[i].nombre);
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        while (1) {
            printf("Velocidad del viento: ");
            if (scanf("%f", &zonas[i].actual.velocidad_viento) != 1 || zonas[i].actual.velocidad_viento < 0) {
                fprintf(stderr, "Error al leer la velocidad del viento para %s. Ingrese un valor valido (positivo).\n", zonas[i].nombre);
                while(getchar() != '\n');
            } else {
                break;
            }
        }

        while (1) {
            printf("Humedad: ");
            if (scanf("%f", &zonas[i].actual.humedad) != 1 || zonas[i].actual.humedad < 0) {
                fprintf(stderr, "Error al leer la humedad para %s. Ingrese un valor valido (positivo).\n", zonas[i].nombre);
                while(getchar() != '\n');
            } else {
                break;
            }
        }
    }
    return 0;
}

void mostrar_predicciones(const Zona *zonas) {
    if (zonas == NULL) return;
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Predicciones para %s en las proximas 24 horas:\n", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            if (isnan(zonas[i].prediccion.niveles[j])) {
                printf("%s: No se pudo calcular la prediccion (datos invalidos).\n", NOMBRE_CONTAMINANTES[j]);
            } else {
                printf("%s: %.2f\n", NOMBRE_CONTAMINANTES[j], zonas[i].prediccion.niveles[j]);
            }
        }
    }
}

void calcular_promedios_historicos(Zona *zonas) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            float suma = 0;
            for (int k = 0; k < DIAS_HISTORICOS; k++) {
                suma += zonas[i].historico[k].niveles[j];
            }
            zonas[i].promedios_historicos[j] = suma / DIAS_HISTORICOS;
        }
    }
}

void mostrar_comparacion_oms(const Zona *zonas) {
    printf("\nComparacion con limites de la OMS:\n");
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Zona: %s\n", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            printf("%s: Promedio Historico: %.2f, Limite OMS: %.2f ", NOMBRE_CONTAMINANTES[j], zonas[i].promedios_historicos[j], LIMITES_OMS[j]);
            if (zonas[i].promedios_historicos[j] > LIMITES_OMS[j]) {
                printf("(Excede el limite)\n");
            } else {
                printf("(Dentro del limite)\n");
            }
        }
    }
}

void calcular_predicciones(Zona *zonas) {
    for (int i = 0; i < NUM_ZONAS; i++) {
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            float valores_historicos[DIAS_HISTORICOS];
            for (int k = 0; k < DIAS_HISTORICOS; k++) {
                valores_historicos[k] = zonas[i].historico[k].niveles[j];
            }
            int error = 0;
            float prediccion_base = promedio_ponderado(valores_historicos, DIAS_HISTORICOS, &error);
            if(error) {
                zonas[i].prediccion.niveles[j] = NAN;
                continue;
            }
            zonas[i].prediccion.niveles[j] = prediccion_base * (1 + (zonas[i].actual.temperatura - 20) * 0.01 + (zonas[i].actual.velocidad_viento - 10) * 0.005);
        }
    }
}

void generar_alertas_y_recomendaciones(const Zona *zonas) {
    printf("\nAlertas y Recomendaciones:\n");
    for (int i = 0; i < NUM_ZONAS; i++) {
        printf("Zona: %s\n", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            float nivel_actual = zonas[i].actual.niveles[j];
            float nivel_prediccion = zonas[i].prediccion.niveles[j];
            if (nivel_prediccion > LIMITES_OMS[j]) {
                printf("%s: Prediccion %.2f (Excede limite OMS de %.2f)\n", NOMBRE_CONTAMINANTES[j], nivel_prediccion, LIMITES_OMS[j]);
                printf("    Alerta: El nivel de %s puede ser perjudicial para la salud. Se recomienda evitar actividades al aire libre.\n", NOMBRE_CONTAMINANTES[j]);
            } else {
                printf("%s: Prediccion %.2f (Dentro del limite OMS de %.2f)\n", NOMBRE_CONTAMINANTES[j], nivel_prediccion, LIMITES_OMS[j]);
                printf("    Recomendacion: Los niveles de %s son dentro de lo esperado. Se recomienda monitorear regularmente.\n", NOMBRE_CONTAMINANTES[j]);
            }

            if (nivel_actual > LIMITES_OMS[j]) {
                printf("    Alerta: El nivel de %s en tiempo real es elevado. Evite permanecer en exteriores por periodos largos.\n", NOMBRE_CONTAMINANTES[j]);
            } else {
                printf("    Recomendacion: El nivel de %s es adecuado, pero siga monitoreando.\n", NOMBRE_CONTAMINANTES[j]);
            }
        }
    }
}

void ejecutar_menu(Zona *zonas) {
    int opcion;
    do {
        printf("\nMenu de Opciones:\n");
        printf("1. Ingresar datos actuales\n");
        printf("2. Simular datos historicos\n");
        printf("3. Calcular predicciones\n");
        printf("4. Mostrar comparacion con limites OMS\n");
        printf("5. Generar alertas y recomendaciones\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                ingresar_datos_actuales(zonas);
                break;
            case 2:
                simular_datos_historicos(zonas);
                break;
            case 3:
                calcular_predicciones(zonas);
                mostrar_predicciones(zonas);
                break;
            case 4:
                calcular_promedios_historicos(zonas);
                mostrar_comparacion_oms(zonas);
                break;
            case 5:
                generar_alertas_y_recomendaciones(zonas);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
    } while (opcion != 6);
}
