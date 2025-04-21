#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"
#include "validator.h"

#define MAX_LINE_LEN 256

CityData* read_city_data(const char* filename, int* city_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error abriendo archivo");
        return NULL;
    }

    char line[MAX_LINE_LEN];
    int capacity = 1000;
    int count = 0;
    CityData* cities = malloc(sizeof(CityData) * capacity);
    if (!cities) {
        perror("Error de memoria");
        fclose(file);
        return NULL;
    }

    fgets(line, MAX_LINE_LEN, file); // Saltar encabezado

    while (fgets(line, MAX_LINE_LEN, file)) {
        if (count >= capacity) {
            capacity *= 2;
            CityData* temp = realloc(cities, sizeof(CityData) * capacity);
            if (!temp) {
                perror("Error de realloc");
                free(cities);
                fclose(file);
                return NULL;
            }
            cities = temp;
        }

        CityData city;
        char risk_str[20] = "";
        int fields = sscanf(line, "%49s %d %19s", city.city_name, &city.seismic_level, risk_str);

        if (!is_valid_seismic_level(city.seismic_level)) {
            printf("Nivel sísmico inválido en línea: %s", line);
            continue;
        }

        if (fields == 3 && strlen(risk_str) > 0) {
            city.risk_percent = atof(risk_str);
            if (!is_valid_risk_percent(city.risk_percent)) {
                printf("Porcentaje de riesgo inválido en línea: %s", line);
                continue;
            }
            city.has_risk_percent = 1;
        } else {
            city.has_risk_percent = 0;
        }

        cities[count++] = city;
    }

    fclose(file);
    *city_count = count;
    return cities;
}

void free_city_data(CityData* data) {
    free(data);
}