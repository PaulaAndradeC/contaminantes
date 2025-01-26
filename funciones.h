#ifndef FUNCIONES_H
#define FUNCIONES_H

#define NUM_ZONAS 5
#define NUM_CONTAMINANTES 4
#define NUM_DIAS_HISTORICOS 30 

typedef struct {
    float niveles_contaminantes[NUM_CONTAMINANTES];
    float temperatura;
    float velocidad_viento;
    float humedad;
    float historial_contaminacion[NUM_DIAS_HISTORICOS][NUM_CONTAMINANTES];  
} Zona;


void ingresar_datos_actuales(Zona zonas[NUM_ZONAS]);
void calcular_niveles_contaminacion_actual(Zona zonas[NUM_ZONAS]);
void calcular_predicciones(Zona zonas[NUM_ZONAS]);
void mostrar_comparacion_oms(Zona zonas[NUM_ZONAS]);
void generar_alertas_y_recomendaciones(Zona zonas[NUM_ZONAS]);
void calcular_promedios_historicos(Zona zonas[NUM_ZONAS]);
void exportar_datos(Zona zonas[NUM_ZONAS]);

extern const char *NOMBRE_CONTAMINANTES[NUM_CONTAMINANTES];
extern const float LIMITES_OMS[NUM_CONTAMINANTES];

#endif

