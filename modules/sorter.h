#ifndef SORTER_H
#define SORTER_H

#include "processor.h"

extern void reorder_level3(CityData *cities, int num_cities);  // Declaración externa
extern void sort_cities(CityData *cities, int num_cities);  // Declaración de sort_cities

int compare(const void *a, const void *b);

#endif