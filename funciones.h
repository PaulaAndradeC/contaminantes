#ifndef FUNCIONES_H
#define FUNCIONES_H

#define NUM_ZONAS 3
#define NUM_CONTAMINANTES 4
#define DIAS_HISTORICOS 7

typedef struct {
    float niveles[NUM_CONTAMINANTES];
    float temperatura;
    float velocidad_viento;
    float humedad;
} Datos;

typedef struct {
    float niveles[NUM_CONTAMINANTES];
} Prediccion;

typedef struct {
    float niveles[NUM_CONTAMINANTES];
} Historico;

typedef struct {
    char nombre[50];
    Datos actual;
    Prediccion prediccion;
    Historico historico[DIAS_HISTORICOS];
    float promedios_historicos[NUM_CONTAMINANTES];
} Zona;

float promedio_ponderado(const float *valores, int n, int *error);
int guardar_datos(const Zona *zonas, const char *nombre_archivo);
int cargar_datos(Zona *zonas, const char *nombre_archivo);
void simular_datos_historicos(Zona *zonas);
int ingresar_datos_actuales(Zona *zonas);
void mostrar_predicciones(const Zona *zonas);
void calcular_promedios_historicos(Zona *zonas);
void mostrar_comparacion_oms(const Zona *zonas);
void calcular_predicciones(Zona *zonas);
void generar_alertas_y_recomendaciones(const Zona *zonas);
void ejecutar_menu(Zona *zonas);

#endif
