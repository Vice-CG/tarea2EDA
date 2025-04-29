#include "sorter.h"
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    const CityData *city1 = (const CityData *)a;
    const CityData *city2 = (const CityData *)b;

    // 1. Comparar nivel sísmico (de mayor a menor)
    if (city2->seismic_level != city1->seismic_level)
        return city2->seismic_level - city1->seismic_level;

    // 2. Si tienen el mismo nivel, aplicar reglas según nivel
    int level = city1->seismic_level;

    // Si ambos tienen o ambos no tienen riesgo, comparamos por riesgo
    if (city1->risk_missing == city2->risk_missing) {
        if (!city1->risk_missing) { // Ambos tienen riesgo, comparamos risk_percent
            if (city2->risk_percent != city1->risk_percent)
                return (city2->risk_percent - city1->risk_percent) > 0 ? 1 : -1;
        }
        // Si ambos tienen missing, o ambos tienen riesgo igual, comparar nombres
        return strcmp(city1->city_name, city2->city_name);
    }

    // Si uno tiene y el otro no, aplicamos regla personalizada según nivel
    if (level == 5 || level == 4) {
        // Falta riesgo -> Más arriba
        return city1->risk_missing ? -1 : 1;
    } else if (level == 3) {
        // Falta riesgo -> Justo en la mitad. Después lo acomodamos con reorder_level3
        return city1->risk_missing ? 1 : -1;
    } else if (level == 2) {
        // Falta riesgo -> Debajo de los nivel 2 con riesgo
        return city1->risk_missing ? 1 : -1;
    } else if (level == 1) {
        // Falta riesgo -> Igual de últimos
        return city1->risk_missing ? 1 : -1;
    }

    return 0; // Por defecto, iguales
}

void reorder_level3(CityData *cities, int num_cities) {
    int start = -1, end = -1;
    for (int i = 0; i < num_cities; i++) {
        if (cities[i].seismic_level == 3) {
            if (start == -1) start = i;
            end = i;
        }
    }

    if (start == -1) return; // No hay level 3

    int count = end - start + 1;

    CityData with_risk[count];
    CityData no_risk[count];
    int with_risk_count = 0, no_risk_count = 0;

    for (int i = start; i <= end; i++) {
        if (cities[i].risk_missing)
            no_risk[no_risk_count++] = cities[i];
        else
            with_risk[with_risk_count++] = cities[i];
    }

    // Ahora reconstruimos: mitad de los que tienen risk, luego los missing, luego el resto
    int idx = start;
    int half = with_risk_count / 2;

    for (int i = 0; i < half; i++)
        cities[idx++] = with_risk[i];

    for (int i = 0; i < no_risk_count; i++)
        cities[idx++] = no_risk[i];

    for (int i = half; i < with_risk_count; i++)
        cities[idx++] = with_risk[i];
}

void sort_cities(CityData *cities, int count) {
    qsort(cities, count, sizeof(CityData), compare);
    reorder_level3(cities, count);
}

