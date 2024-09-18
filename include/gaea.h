#ifndef GAEA_H
#define GAEA_H

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
    } value;
} GaeaValue;

GaeaValue gaea_create_null(void);
GaeaValue gaea_create_boolean(int value);
GaeaValue gaea_create_integer(int64_t value);
GaeaValue gaea_create_double(double value);
GaeaValue gaea_create_string(const char *value);

void gaea_free_value(GaeaValue *value);

#endif // GAEA_H