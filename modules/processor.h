#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct {
    char city_name[50];
    int seismic_level;
    float risk_percent;
    int has_risk_percent;
    int risk_missing;
    int priority;
} CityData;

CityData* read_city_data(const char* filename, int* city_count);
void free_city_data(CityData* data);

// CAMBIO AQUÍ: usamos int, no float
int get_priority(int seismic_level, int risk_missing);

int load_city_data(const char *filename, CityData **cities_out, int *count_out);

#endif