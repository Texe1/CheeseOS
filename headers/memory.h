#pragma once

#include "typedefs.h"
#include "screen.h"

typedef struct{
    u64 baseAddress;
    u64 length;
    u32 type;
    u32 extendedAttributes;
} MemoryMapDescriptor;

typedef struct MemorySegmentDescriptor{
    u64 size;
    struct MemorySegmentDescriptor* next;
    struct MemorySegmentDescriptor* previous;
    u8 free; // non-zero if free
} MemorySegmentDescriptor;

extern u8 MEMORYREGIONCOUNT;

extern MemoryMapDescriptor MEMORYREGIONDESCRIPTORS;

MemorySegmentDescriptor *firstMemorySegment;

MemoryMapDescriptor **getUsableMemoryRegions();

u8 getUsableMemoryAmount();

void InitializeHeap();

void *malloc(u64 size);

void *calloc(u64 size, u64 value);

void free(void *mallocVal);