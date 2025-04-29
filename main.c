#include <stdio.h>
#include <stdlib.h>
#include "modules/processor.h"
#include "modules/sorter.h"

int main(int argc, char *argv[]) {
    // Comprobamos que el programa reciba exactamente 3 argumentos: input, N y output
    if (argc != 4) {
        printf("Uso: %s <input> <N> <output>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1]; // nombre del archivo de entrada
    int N = atoi(argv[2]); // cantidad de ciudades a mostrar
    const char *output_file = argv[3]; // nombre del archivo de salida

    CityData *cities = NULL;
    int count = 0;
 
    // Cargar los datos de las ciudades desde el archivo CSV

    if (!load_city_data(input_file, &cities, &count)) {
        perror("Error al cargar los datos");
        return 1;
    }
    // Llama a la función void sort_cities de sorter.c ( ordena las ciudades según nombre (Z-A), las reglas de prioridad sísmica y riesgo)

    sort_cities(cities, count);

    // Carga de datos desde el archivo CSV

    FILE *fout = fopen(output_file, "w");
    if (!fout) {
        perror("No se pudo abrir el archivo de salida");
        free(cities);
        return 1;
    }
   // Escribimos encabezado
fprintf(fout, "city_name,seismic_level,risk_percent\n");



// Escribimos las  N ciudades

for (int i = 0; i < N && i < count; i++) {

      // Si falta el porcentaje de riesgo, lo dejamos vacío

    if (cities[i].risk_missing) {
        fprintf(fout, "%s,%d,\n", cities[i].city_name, cities[i].seismic_level);

         // Si existe porcentaje de riesgo, lo escribimos con dos decimales

    } else {
        fprintf(fout, "%s,%d,%.2f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
    }
}

    fclose(fout);
    free(cities); // Liberamos la memoria dinámica usada
    return 0;
}
