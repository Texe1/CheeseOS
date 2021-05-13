#include "headers/IO.h"
#include "headers/String.h"
#include "headers/IDT.h"
#include "headers/screen.h"
#include "headers/memory.h"

u64 *videoMem = (u64*)0xa0000;

void _start(){
    IDTInit();
    getUsableMemoryRegions();
    InitializeHeap();
    void* mallocVal = malloc(0x10);
    // clearScreen(0x0f);
    videoMem[0] = ((u64)mallocVal) != 0 ? 0x0f0f0f0f0f0f0f0f : 0x0;
    
    mallocVal = malloc(0x10);
    // videoMem[0] = 0x0f0f0f0f0f0f0f0f;
    // clearScreen(getUsableMemoryAmount());
    return;
}