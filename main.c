#include <stdio.h>
#include <stdlib.h>
typedef struct {
 char city_name[50];
 int seismic_level;
 float risk_percent;
} CityData;
int main(int argc, char *argv[]) {
 if (argc != 4) {
 printf("Uso: %s <input> <N> <output>\n", argv[0]);
 return 1;
 }
 // Implementación pendiente
 return 0;
}
