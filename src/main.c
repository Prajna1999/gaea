#include <stdio.h>
#include "gaea.h"

int main()
{
    printf("Welcome to Gaea Database!\n");

    // Example usage of our GaeaValue types
    GaeaValue null_value = gaea_create_null();
    GaeaValue bool_value = gaea_create_boolean(1);
    GaeaValue int_value = gaea_create_integer(42);
    GaeaValue double_value = gaea_create_double(3.14);
    GaeaValue string_value = gaea_create_string("Hello, Gaea!");

    printf("Created GaeaValue types:\n");
    printf("Null: type = %d\n", null_value.type);
    printf("Boolean: type = %d, value = %d\n", bool_value.type, bool_value.value.boolean);
    printf("Integer: type = %d, value = %ld\n", int_value.type, int_value.value.integer);
    printf("Double: type = %d, value = %f\n", double_value.type, double_value.value.floating);
    printf("String: type = %d, value = %s\n", string_value.type, string_value.value.string);

    // Don't forget to free the string value
    gaea_free_value(&string_value);

    return 0;
}