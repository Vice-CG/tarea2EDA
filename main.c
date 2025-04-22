#include <stdio.h> //Función para leer y procesar datos
#include <stdlib.h> //Función para manejo y ordenamiento de memoria 
#include <string.h> //Función para trabajar con cadenas de texto (ordenamiento por nombre inverso de la Z-A)

#define MAX_LINE 256

typedef struct {
    char city_name[50]; //Nombre de la ciudad
    int seismic_level; //Nivel sísmico
    float risk_percent; //Probabilidad de actividad sísmica
    int priority;  // Prioridad de valores faltantes
} CityData;

// === Función para calcular la prioridad de datos faltantes
int get_priority(int seismic_level, float risk_percent) {
    if (seismic_level == 0 || risk_percent == 0.0) {
        return 2;  // Alta prioridad por datos faltantes
    }
    
    if (seismic_level >= 4) return 2;  // Alta prioridad para niveles 4 y 5
    if (seismic_level == 3) return 1;  // Prioridad media para nivel 3
    return 0;  // Baja prioridad para niveles 1 y 2
}

// Comparador con qsort
int compare(const void *a, const void *b) {
    const CityData *city1 = (CityData *)a;
    const CityData *city2 = (CityData *)b;

    // Primero, comparar la prioridad
    if (city2->priority != city1->priority) {
        return city2->priority - city1->priority;  // Descendente (mayor prioridad primero)
    }

 // Si son iguales, comparar por nivel sísmico
 if (city2->seismic_level != city1->seismic_level) {
    return city2->seismic_level - city1->seismic_level;  // Descendente (mayor nivel sísmico primero)
}


    // Si son iguales, comparar por porcentaje de riesgo
    if (city2->risk_percent != city1->risk_percent) {
        return (city2->risk_percent - city1->risk_percent) > 0 ? 1 : -1;  // Descendente (mayor riesgo primero)
    }

   
    // Si todo es igual, desempatar por nombre de la ciudad en orden inverso (Z-A)
    return strcmp(city2->city_name, city1->city_name);  // Z-A
}

// === Función principal
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <input> <N> <output>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    int N = atoi(argv[2]);
    const char *output_file = argv[3];

    FILE *fin = fopen(input_file, "r");
    if (!fin) {
        perror("No se pudo abrir el archivo de entrada");
        return 1;
    }

    // Arreglo dinámico
    int capacity = 1000;
    int count = 0;
    CityData *cities = malloc(capacity * sizeof(CityData));
    if (!cities) {
        perror("Fallo al reservar memoria");
        fclose(fin);
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fin)) {
        if (count >= capacity) {
            capacity *= 2;
            cities = realloc(cities, capacity * sizeof(CityData));
            if (!cities) {
                perror("Fallo al redimensionar memoria");
                fclose(fin);
                return 1;
            }
        }

        char *token = strtok(line, ",");
        if (!token) continue;
        strncpy(cities[count].city_name, token, 49);
        cities[count].city_name[49] = '\0';

        // Leer seismic_level
        token = strtok(NULL, ",");
        int level = 0;
        if (token && sscanf(token, "%d", &level) == 1 && level >= 1 && level <= 5) {
            cities[count].seismic_level = level;
        } else {
            cities[count].seismic_level = 0; // Campo vacío o inválido
        }

        // Leer risk_percent
        token = strtok(NULL, ",");
        float risk = 0;
        if (token && sscanf(token, "%f", &risk) == 1 && risk >= 0 && risk <= 100) {
            cities[count].risk_percent = risk;
        } else {
            cities[count].risk_percent = 0.0; // Campo vacío o inválido
        }

        cities[count].priority = get_priority(cities[count].seismic_level, cities[count].risk_percent);
        count++;
    }

    fclose(fin);

    // Ordenar por prioridad
    qsort(cities, count, sizeof(CityData), compare);

    // Guardar en archivo de salida
    FILE *fout = fopen(output_file, "w");
    if (!fout) {
        perror("No se pudo abrir el archivo de salida");
        free(cities);
        return 1;
    }

    for (int i = 0; i < N && i < count; i++) {
        fprintf(fout, "%s,%d,%.2f\n",
                cities[i].city_name,
                cities[i].seismic_level,
                cities[i].risk_percent);
    }

    fclose(fout);
    free(cities);

    return 0;
}


