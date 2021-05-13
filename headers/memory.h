#pragma once

#include "typedefs.h"

typedef struct MemoryMapDescriptor{
    u64 baseAddress;
    u64 length;
    u32 type;
    u32 extendedAttributes;
} MemoryMapDescriptor;

MemoryMapDescriptor **getUsableMemoryRegions();