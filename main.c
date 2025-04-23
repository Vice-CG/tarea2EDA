#include <stdio.h>
#include <stdlib.h>
#include "modules/processor.h"
#include "modules/sorter.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <input> <N> <output>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    int N = atoi(argv[2]);
    const char *output_file = argv[3];

    CityData *cities = NULL;
    int count = 0;

    if (!load_city_data(input_file, &cities, &count)) {
        perror("Error al cargar los datos");
        return 1;
    }

    qsort(cities, count, sizeof(CityData), compare);

    FILE *fout = fopen(output_file, "w");
    if (!fout) {
        perror("No se pudo abrir el archivo de salida");
        free(cities);
        return 1;
    }
   // Escribimos encabezado
fprintf(fout, "city_name,seismic_level,risk_percent\n");

for (int i = 0; i < N && i < count; i++) {
    if (cities[i].risk_missing) {
        fprintf(fout, "%s,%d,\n", cities[i].city_name, cities[i].seismic_level);
    } else {
        fprintf(fout, "%s,%d,%.2f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
    }
}

    fclose(fout);
    free(cities);
    return 0;
}
