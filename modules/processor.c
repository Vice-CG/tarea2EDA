#include "processor.h"
#include "validator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

int get_priority(int level, int risk_missing) {
    if (level >= 4) {
        return 5;  // Alta prioridad aunque falte riesgo
    } else if (level == 3) {
        return risk_missing ? 3 : 4;  // 4 si tiene riesgo, 3 si le falta
    } else if (level == 1 || level == 2) {
        return risk_missing ? 0 : 1;  // 1 si tiene riesgo, 0 si le falta
    }
    return 0;  // Nivel inválido o sin datos
}

int load_city_data(const char *filename, CityData **cities_out, int *count_out) {
    FILE *fin = fopen(filename, "r");
    if (!fin) return 0;

    int capacity = 1000;
    int count = 0;
    CityData *cities = malloc(capacity * sizeof(CityData));
    if (!cities) {
        fclose(fin);
        return 0;
    }

    char line[MAX_LINE];

    // Saltar la primera línea (encabezado)
    if (!fgets(line, sizeof(line), fin)) {
        fclose(fin);
        free(cities);
        return 0;
    }

    while (fgets(line, sizeof(line), fin)) {
        if (count >= capacity) {
            capacity *= 2;
            cities = realloc(cities, capacity * sizeof(CityData));
            if (!cities) {
                fclose(fin);
                return 0;
            }
        }

        char *token = strtok(line, ",");
        if (!token) continue;
        strncpy(cities[count].city_name, token, 49);
        cities[count].city_name[49] = '\0';

        token = strtok(NULL, ",");
        int level = 0;
        if (token && is_valid_level(token)) {
            sscanf(token, "%d", &level);
        }
        cities[count].seismic_level = level;

        token = strtok(NULL, ",");
        float risk = 0.0;
        if (token && sscanf(token, "%f", &risk) == 1 && risk >= 0 && risk <= 100) {
            cities[count].risk_percent = risk;
            cities[count].risk_missing = 0;
        } else {
            cities[count].risk_percent = 0.0;
            cities[count].risk_missing = 1;  // dato faltante
        }

        cities[count].priority = get_priority(level, cities[count].risk_missing);
        count++;
    }

    fclose(fin);
    *cities_out = cities;
    *count_out = count;
    return 1;
}