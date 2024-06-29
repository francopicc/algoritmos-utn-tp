#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TRADERS 4
#define NUM_DAYS 90
#define NUM_COMBINATIONS 3

typedef struct {
    char nombre[50];
    int observaciones;
    int positivas;
} Combinacion;

typedef struct {
    Combinacion combinaciones[NUM_COMBINATIONS];
} Dia;

typedef struct {
    Dia dias[NUM_DAYS];
} Trader;

// Funcion para inicializar datos de combinaciones
void inicializar_combinaciones(Combinacion combinaciones[NUM_COMBINATIONS]) {
    strcpy(combinaciones[0].nombre, "MACD + Cruce Medias 8/40");
    combinaciones[0].observaciones = 0;
    combinaciones[0].positivas = 0;

    strcpy(combinaciones[1].nombre, "RSI + MACD");
    combinaciones[1].observaciones = 0;
    combinaciones[1].positivas = 0;

    strcpy(combinaciones[2].nombre, "Elliot + Volumen");
    combinaciones[2].observaciones = 0;
    combinaciones[2].positivas = 0;
}

// Funcion para simular datos de trading
void simular_datos(Trader traders[NUM_TRADERS]) {
    for (int i = 0; i < NUM_TRADERS; i++) {
        for (int j = 0; j < NUM_DAYS; j++) {
            inicializar_combinaciones(traders[i].dias[j].combinaciones);
            for (int k = 0; k < NUM_COMBINATIONS; k++) {
                traders[i].dias[j].combinaciones[k].observaciones = rand() % 10;
                traders[i].dias[j].combinaciones[k].positivas = rand() % (traders[i].dias[j].combinaciones[k].observaciones + 1);
            }
        }
    }
}

// Funcion para contar observaciones
void contar_observaciones(Trader traders[NUM_TRADERS], Combinacion conteo[NUM_COMBINATIONS]) {
    for (int i = 0; i < NUM_COMBINATIONS; i++) {
        conteo[i].observaciones = 0;
        conteo[i].positivas = 0;
    }

    for (int i = 0; i < NUM_TRADERS; i++) {
        for (int j = 0; j < NUM_DAYS; j++) {
            for (int k = 0; k < NUM_COMBINATIONS; k++) {
                conteo[k].observaciones += traders[i].dias[j].combinaciones[k].observaciones;
                conteo[k].positivas += traders[i].dias[j].combinaciones[k].positivas;
            }
        }
    }
}

// Funcion para calcular y mostrar porcentajes
void calcular_porcentajes(Combinacion conteo[NUM_COMBINATIONS]) {
    for (int i = 0; i < NUM_COMBINATIONS; i++) {
        printf("Combinacion: %s\n", conteo[i].nombre);
        if (conteo[i].observaciones > 0) {
            double porcentaje = (double)conteo[i].positivas / conteo[i].observaciones * 100.0;
            printf("Observaciones: %d, Positivas: %d, Porcentaje: %.2f%%\n\n",
                   conteo[i].observaciones, conteo[i].positivas, porcentaje);
        } else {
            printf("No hay observaciones.\n\n");
        }
    }
}

// Funcion para analizar frecuencias
void analizar_frecuencias(Combinacion conteo[NUM_COMBINATIONS]) {
    int max_idx = 0, min_idx = 0;
    for (int i = 1; i < NUM_COMBINATIONS; i++) {
        if (conteo[i].observaciones > conteo[max_idx].observaciones) {
            max_idx = i;
        }
        if (conteo[i].observaciones < conteo[min_idx].observaciones) {
            min_idx = i;
        }
    }

    printf("Combinacion mas observada: %s con %d observaciones\n", conteo[max_idx].nombre, conteo[max_idx].observaciones);
    printf("Combinacion menos observada: %s con %d observaciones\n", conteo[min_idx].nombre, conteo[min_idx].observaciones);
}

// Funcion para analizar dias especificos
void analizar_dias_especificos(Trader traders[NUM_TRADERS]) {
    int conteo_fines_semana[NUM_COMBINATIONS] = {0};
    int conteo_mediados_semana[NUM_COMBINATIONS] = {0};

    for (int i = 0; i < NUM_TRADERS; i++) {
        for (int j = 0; j < NUM_DAYS; j++) {
            if (j % 7 == 5 || j % 7 == 6) { // Fines de semana (sabado=5, domingo=6)
                for (int k = 0; k < NUM_COMBINATIONS; k++) {
                    conteo_fines_semana[k] += traders[i].dias[j].combinaciones[k].observaciones;
                }
            } else if (j % 7 == 2 || j % 7 == 3 || j % 7 == 4) { // Mediados de semana (martes=2, miercoles=3, jueves=4)
                for (int k = 0; k < NUM_COMBINATIONS; k++) {
                    conteo_mediados_semana[k] += traders[i].dias[j].combinaciones[k].observaciones;
                }
            }
        }
    }

    int max_fines_semana_idx = 0, max_mediados_semana_idx = 0;
    for (int i = 1; i < NUM_COMBINATIONS; i++) {
        if (conteo_fines_semana[i] > conteo_fines_semana[max_fines_semana_idx]) {
            max_fines_semana_idx = i;
        }
        if (conteo_mediados_semana[i] > conteo_mediados_semana[max_mediados_semana_idx]) {
            max_mediados_semana_idx = i;
        }
    }

    printf("Combinacion mas observada en fines de semana: %s con %d observaciones\n", 
           traders[0].dias[0].combinaciones[max_fines_semana_idx].nombre, conteo_fines_semana[max_fines_semana_idx]);
    printf("Combinacion mas observada en mediados de semana: %s con %d observaciones\n", 
           traders[0].dias[0].combinaciones[max_mediados_semana_idx].nombre, conteo_mediados_semana[max_mediados_semana_idx]);
}

int main() {
    Trader traders[NUM_TRADERS];
    Combinacion conteo[NUM_COMBINATIONS];

    simular_datos(traders);
    contar_observaciones(traders, conteo);
    calcular_porcentajes(conteo);
    analizar_frecuencias(conteo);
    analizar_dias_especificos(traders);

    return 0;
}

