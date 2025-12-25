#ifndef ARENA_ALLOC_H
#define ARENA_ALLOC_H

#include "common.h"

typedef struct Arena
{
    u64 _capacity;
    u64 _offset;
} Arena;

Arena*  CreateArena();
void    ClearArena(Arena* arena);
void    DestroyArena(Arena* arena);

void*   _ArenaAllocate(Arena* arena, u64 size);

#define ArenaPush(arena, type)              (type*)_ArenaAllocate((arena), sizeof(type))
#define ArenaPushStruct(arena, type)        (type*)_ArenaAllocate((arena), sizeof(type))
#define ArenaPushArray(arena, type, count)  (type*)_ArenaAllocate((arena), sizeof(type) * (count))

#endif // ARENA_ALLOC_H