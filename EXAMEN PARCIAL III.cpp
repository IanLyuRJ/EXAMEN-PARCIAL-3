#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLUMNAS 3100
#define FILAS_A_PROCESAR 50
#define BUFFER_SIZE 1024*1024 

int main() {
    const char *nombre_archivo_csv = "emails.csv";
    FILE *archivo_csv = fopen(nombre_archivo_csv, "r");
    if (!archivo_csv) {
        perror("Error al abrir el archivo CSV");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int conteo_palabras[MAX_COLUMNAS] = {0};
    char *nombres_palabras[MAX_COLUMNAS];
    int fila_inicio = 780;  

   
    if (fgets(buffer, sizeof(buffer), archivo_csv) != NULL) {
        char *token = strtok(buffer, ",");
        int indice_columna = 0;
        while (token && indice_columna < MAX_COLUMNAS) {
            nombres_palabras[indice_columna++] = strdup(token);
            token = strtok(NULL, ",");
        }
    } else {
        fprintf(stderr, "No se pudo leer la primera línea del archivo CSV.\n");
        fclose(archivo_csv);
        return 1;
    }

 
    for (int i = 0; i < fila_inicio; ++i) {
        if (fgets(buffer, sizeof(buffer), archivo_csv) == NULL) {
            fprintf(stderr, "No se pudo llegar a la fila de inicio.\n");
            fclose(archivo_csv);
            return 1;
        }
    }

 
    for (int i = 0; i < FILAS_A_PROCESAR; ++i) {
        if (fgets(buffer, sizeof(buffer), archivo_csv) == NULL) {
            break;  
        }
        char *token = strtok(buffer, ",");
        int indice_columna = 0;
        while (token && indice_columna < MAX_COLUMNAS) {
            if (indice_columna > 0) {  
                conteo_palabras[indice_columna - 1] += atoi(token);
            }
            token = strtok(NULL, ",");
            indice_columna++;
        }
    }

    fclose(archivo_csv);

   
    FILE *archivo_salida = fopen("181780.txt", "w");
    if (!archivo_salida) {
        perror("Error al abrir el archivo de salida");
        return 1;
    }

    for (int i = 0; i < MAX_COLUMNAS - 1; i++) {
        if (nombres_palabras[i] != NULL) {
            fprintf(archivo_salida, "%s, %d\n", nombres_palabras[i], conteo_palabras[i]);
            free(nombres_palabras[i]); 
        }
    }

    fclose(archivo_salida);
    printf("Los conteos de palabras han sido escritos en 181780.txt\n");

    return 0;
}

