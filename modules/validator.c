#include "validator.h"
#include <stdlib.h>

int is_valid_level(const char *token) {
    int level = atoi(token);
    return level >= 1 && level <= 5;
}

int is_valid_risk(const char *token) {
    float risk = atof(token);
    return risk >= 0.0 && risk <= 100.0;
}