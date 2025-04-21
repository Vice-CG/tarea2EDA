#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct {
    char city_name[50];
    int seismic_level;
    float risk_percent;
    int has_risk_percent;
} CityData;

CityData* read_city_data(const char* filename, int* city_count);
void free_city_data(CityData* data);

#endif