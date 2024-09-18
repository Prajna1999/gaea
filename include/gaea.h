#ifndef GAEA_H
#define GAEA_H

// Gaea database function declarations will go here

#include <stdint.h>

typedef enum
{
    GAEA_NULL,
    GAEA_BOOLEAN,
    GAEA_INTEGER,
    GAEA_DOUBLE,
    GAEA_STRING,
} GaeaValueType;

typedef struct
{
    GaeaValueType type;
    union
    {
        int boolean;
        int64_t integer;
        double floating;
        char *string;
    } value
} GaeaValue;

// functions to create different types of GaeaValues:
GaeaValue gaea_create_null();
GaeaValue gaea_craete_boolean(int value);
GaeaValue gaea_craete_integer(int64_t value);
GaeaValue gaea_create_double(double value);
GaeaValue gaea_craete_string(const char *value);

// Function to free any resources associated with a GaeaValue:
void gaea_free_value(GaeaValue *value);

#endif // GAEA_H
