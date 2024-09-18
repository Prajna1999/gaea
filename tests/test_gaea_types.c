#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "gaea.h"
#define TEST(name) void name()

TEST(test_gaea_null)
{
    GaeaValue v = gaea_create_null();
    assert(v.type == GAEA_NULL);
}

TEST(test_gaea_boolean)
{
    GaeaValue v = gaea_create_boolean(1);
    assert(v.type == GAEA_BOOLEAN);
    assert(v.value.boolean == 1);
}

TEST(test_gaea_integer)
{
    GaeaValue v = gaea_create_integer(12345);
    assert(v.type == GAEA_INTEGER);
    assert(v.value.integer == 12345);
}

TEST(test_gaea_double)
{
    GaeaValue v = gaea_create_double(3.14159);
    assert(v.type == GAEA_DOUBLE);
    assert(v.value.floating == 3.14159);
}

TEST(test_gaea_string)
{
    const char *test_string = "Hello, Gaea!";
    GaeaValue v = gaea_create_string(test_string);
    assert(v.type == GAEA_STRING);
    assert(strcmp(v.value.string, test_string) == 0);
    gaea_free_value(&v);
}

int main()
{
    printf("Running Gaea type tests...\n");

    test_gaea_null();
    test_gaea_boolean();
    test_gaea_integer();
    test_gaea_double();
    test_gaea_string();

    printf("All tests passed successfully!\n");
    return 0;
}