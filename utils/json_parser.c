#include "json_parser.h"

#include <stdio.h>
#include <assert.h>

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

typedef struct
{
    char*   buffer;
    size_t  position;
    size_t  length;
} JSONContent;

static JSONContent* __readJSONFile(const char* filepath)
{
    assert(!(filepath == NULL) && "filepath is NULL!");

    // Use malloc/free instead of g_hooks.malloc/free because content->buffer
    // may be large and short-lived. Custom hooks may use an arena allocator, 
    // which is not appropriate for large and short-lived allocations.
    JSONContent* content    = (JSONContent*)malloc(sizeof(JSONContent));
    content->buffer         = NULL;
    content->position       = 0;
    content->length         = 0;

    // This method apparently works for small files (approx .<=4GiB)
    FILE* file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file!\n");
        free(content);
        content = NULL;
        return NULL;
    }

    if(fseek(file, 0, SEEK_END) != 0)
    {
        fprintf(stderr, "Failed to reach end of file!\n");
        free(content);
        content = NULL;
        fclose(file);
        return NULL;
    }
    content->length = ftell(file);
    if (fseek(file, 0, SEEK_SET) != 0)
    {
        fprintf(stderr, "Failed to reach start of file!\n");
        free(content);
        content = NULL;
        fclose(file);
        return NULL;
    }

    content->buffer = (char*)malloc(content->length + 1); // Don't check malloc (os will handle)
    if(fread(content->buffer, sizeof(char), content->length, file) != content->length)
    {
        fprintf(stderr, "Failed to read file!\n");
        free(content->buffer);
        free(content);
        content = NULL;
        fclose(file);
        return NULL;
    }
    content->buffer[content->length] = '\0';

    fclose(file);

    return content;
}

static JSON* __parseJSON(JSONContent* content)
{
    (void)content;
    return NULL;
}

JSON* parseJSON(const char* filepath)
{
    JSONContent* content = __readJSONFile(filepath);
    if (content == NULL)
    {
        fprintf(stderr, "Something went wrong with reading the JSON file!\n");
        return NULL;
    }

    JSON* root = __parseJSON(content);
    
    free(content->buffer);
    free(content);
    content = NULL;

    //TODO

    return root;
}

void deleteJSON(JSON* json)
{
    assert(!(json == NULL) && "json is NULL!");

    g_hooks.free(json); 
}