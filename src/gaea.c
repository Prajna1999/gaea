#include "gaea.h"
#include <stdlib.h>
#include <string.h>

GaeaValue gaea_create_null(void)
{
    return (GaeaValue){.type = GAEA_NULL};
}

GaeaValue gaea_create_boolean(int value)
{
    return (GaeaValue){.type = GAEA_BOOLEAN, .value = {.boolean = value}};
}

GaeaValue gaea_create_integer(int64_t value)
{
    return (GaeaValue){.type = GAEA_INTEGER, .value = {.integer = value}};
}

GaeaValue gaea_create_double(double value)
{
    return (GaeaValue){.type = GAEA_DOUBLE, .value = {.floating = value}};
}

GaeaValue gaea_create_string(const char *value)
{
    GaeaValue v = {.type = GAEA_STRING};
    v.value.string = strdup(value);
    return v;
}

void gaea_free_value(GaeaValue *value)
{
    if (value->type == GAEA_STRING)
    {
        free(value->value.string);
        value->value.string = NULL;
    }
}