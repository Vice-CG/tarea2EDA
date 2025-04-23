#include "sorter.h"
#include <string.h>

int compare(const void *a, const void *b) {
    const CityData *city1 = (const CityData *)a;
    const CityData *city2 = (const CityData *)b;

    // 1. Comparar nivel sísmico (de mayor a menor)
    if (city2->seismic_level != city1->seismic_level)
        return city2->seismic_level - city1->seismic_level;

    // 2. Si tienen el mismo nivel, aplicar reglas según nivel
    int level = city1->seismic_level;

    // Si ambos tienen datos o ambos no los tienen, comparamos por riesgo
    if (city1->risk_missing == city2->risk_missing) {
        if (city2->risk_percent != city1->risk_percent)
            return (city2->risk_percent - city1->risk_percent) > 0 ? 1 : -1;
        return strcmp(city1->city_name, city2->city_name); // orden alfabético ascendente si todo es igual
    }

    // Si uno tiene y otro no, aplicamos regla personalizada
    if (level == 5 || level == 4) {
        // Falta riesgo -> más arriba
        return city1->risk_missing ? -1 : 1;
    } else if (level == 3) {
        // Falta riesgo -> justo en la mitad. Lo simulamos dejando los sin riesgo en medio
        return city1->risk_missing ? 1 : -1;
    } else if (level == 2) {
        // Falta riesgo -> debajo de los nivel 2 con riesgo, pero arriba de los nivel 1
        return city1->risk_missing ? 1 : -1;
    } else if (level == 1) {
        // Falta riesgo -> igual de últimos
        return city1->risk_missing ? 1 : -1;
    }

    return 0;
}