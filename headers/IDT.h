#pragma once
#include "typedefs.h"
#include "IO.h"

typedef struct IDT
{
    u16 offset_low;
    u16 selector;
    u8 ist;
    u8 typesAttr;
    u16 offset_mid;
    u32 offset_high;
    u32 zero;
} IDT;

void IDTInit();
