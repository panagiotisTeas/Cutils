#include "json_parser.h"

typedef struct
{
    void* (*malloc)(size_t size);
    void    (*free)(void* ptr);
} InternalHooks;

static InternalHooks g_hooks = {malloc, free};

void InitHooks(JSONHooks* hooks)
{
    if (hooks == NULL)
        return;

    g_hooks.malloc  = hooks->malloc;
    g_hooks.free    = hooks->free;
}

JSON* parseJSON(const char* filepath)
{
    (void)filepath;

    JSON* root = (JSON*)g_hooks.malloc(sizeof(JSON));

    //TODO

    return root;
}

void deleteJSON(JSON* json)
{ (void)json; }