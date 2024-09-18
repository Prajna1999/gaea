#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaea.h"

#define MAX_INPUT 1024
#define MAX_ENTRIES 100

typedef struct
{
    char *key;
    GaeaValue value;
} Entry;

Entry database[MAX_ENTRIES];
int entry_count = 0;

void insert_entry(const char *key, GaeaValue value)
{
    if (entry_count >= MAX_ENTRIES)
    {
        printf("Error: Database is full\n");
        return;
    }

    for (int i = 0; i < entry_count; i++)
    {
        if (strcmp(database[i].key, key) == 0)
        {
            gaea_free_value(&database[i].value);
            database[i].value = value;
            return;
        }
    }

    database[entry_count].key = strdup(key);
    database[entry_count].value = value;
    entry_count++;
}

GaeaValue *get_entry(const char *key)
{
    for (int i = 0; i < entry_count; i++)
    {
        if (strcmp(database[i].key, key) == 0)
        {
            return &database[i].value;
        }
    }
    return NULL;
}

void print_value(GaeaValue *value)
{
    if (value == NULL)
    {
        printf("NULL\n");
        return;
    }

    switch (value->type)
    {
    case GAEA_NULL:
        printf("NULL\n");
        break;
    case GAEA_BOOLEAN:
        printf("%s\n", value->value.boolean ? "true" : "false");
        break;
    case GAEA_INTEGER:
        printf("%ld\n", value->value.integer);
        break;
    case GAEA_DOUBLE:
        printf("%f\n", value->value.floating);
        break;
    case GAEA_STRING:
        printf("%s\n", value->value.string);
        break;
    }
}

void process_command(char *input)
{
    char *command = strtok(input, " ");
    if (command == NULL)
        return;

    if (strcmp(command, "SET") == 0)
    {
        char *key = strtok(NULL, " ");
        char *type = strtok(NULL, " ");
        char *value = strtok(NULL, "");

        if (key == NULL || type == NULL || value == NULL)
        {
            printf("Usage: SET <key> <type> <value>\n");
            return;
        }

        GaeaValue gaea_value;
        if (strcmp(type, "NULL") == 0)
        {
            gaea_value = gaea_create_null();
        }
        else if (strcmp(type, "BOOLEAN") == 0)
        {
            gaea_value = gaea_create_boolean(strcmp(value, "true") == 0);
        }
        else if (strcmp(type, "INTEGER") == 0)
        {
            gaea_value = gaea_create_integer(atoll(value));
        }
        else if (strcmp(type, "DOUBLE") == 0)
        {
            gaea_value = gaea_create_double(atof(value));
        }
        else if (strcmp(type, "STRING") == 0)
        {
            gaea_value = gaea_create_string(value);
        }
        else
        {
            printf("Unknown type: %s\n", type);
            return;
        }

        insert_entry(key, gaea_value);
        printf("OK\n");
    }
    else if (strcmp(command, "GET") == 0)
    {
        char *key = strtok(NULL, " ");
        if (key == NULL)
        {
            printf("Usage: GET <key>\n");
            return;
        }

        GaeaValue *value = get_entry(key);
        print_value(value);
    }
    else if (strcmp(command, "EXIT") == 0)
    {
        printf("Goodbye!\n");
        exit(0);
    }
    else
    {
        printf("Unknown command: %s\n", command);
    }
}

int main()
{
    char input[MAX_INPUT];

    printf("Welcome to Gaea CLI!\n");
    printf("Enter commands (SET, GET, EXIT):\n");

    while (1)
    {
        printf("gaea> ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;
        input[strcspn(input, "\n")] = 0; // Remove newline
        process_command(input);
    }

    // Clean up
    for (int i = 0; i < entry_count; i++)
    {
        free(database[i].key);
        gaea_free_value(&database[i].value);
    }

    return 0;
}