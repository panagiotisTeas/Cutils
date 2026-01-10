#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    void* (*malloc)(size_t size);
    void    (*free)(void* ptr);
} JSONHooks;

void InitHooks(JSONHooks* hooks);

typedef enum
{
    JSON_TYPE_OBJECT = 0,
    JSON_TYPE_ARRAY,
    JSON_TYPE_STRING,
    JSON_TYPE_NUMBER,
    JSON_TYPE_BOOLEAN,
    JSON_TYPE_NULL
} JSONType;

typedef struct
{
    struct JSON*    prev;
    struct JSON*    next;

    char*           key;
    JSONType        type;
    union
    {
        struct JSON*    json; // Object/Array/null
        char*           string;
        double          number;
        bool            boolean;
    }               value;
} JSON;

JSON*   parseJSON(const char* filepath);
void    deleteJSON(JSON* json);

#endif // JSON_PARSER_H