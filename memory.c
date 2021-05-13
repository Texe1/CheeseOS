#include "headers/memory.h"


u8 gotUsableMemory = 0;
u8 usableMemoryAmount = 0;
MemoryMapDescriptor *usableMemory[10];

MemoryMapDescriptor **getUsableMemoryRegions(){

    MemoryMapDescriptor *currentdescriptor = &MEMORYREGIONDESCRIPTORS;

    for (int i = 0; i < MEMORYREGIONCOUNT && usableMemoryAmount < 10; i++)
    {
        if (currentdescriptor->type == 1 && currentdescriptor->length != 0){
            usableMemory[usableMemoryAmount++] = currentdescriptor;
        }
        currentdescriptor++;
    }
    
    return usableMemory;

}

u8 getUsableMemoryAmount(){
    if(gotUsableMemory == 0) getUsableMemoryRegions();
    return usableMemoryAmount;
}

void InitializeHeap(){
    firstMemorySegment = (MemorySegmentDescriptor*)(getUsableMemoryRegions()[1]->baseAddress);
    firstMemorySegment->free = 1;
    firstMemorySegment->next = 0;
    firstMemorySegment->previous = 0;
    firstMemorySegment->size = usableMemory[0]->length - sizeof(MemorySegmentDescriptor);
    
    MemorySegmentDescriptor *currentLastSegment = firstMemorySegment;

    for (u8 i = 1; i < usableMemoryAmount; i++)
    {
        MemorySegmentDescriptor *newSegment = (MemorySegmentDescriptor*)(usableMemory[i]->baseAddress);
        newSegment->free = 1;
        newSegment->next = 0;
        newSegment->previous = 0;
        newSegment->size = usableMemory[i]->length - sizeof(MemorySegmentDescriptor);

        currentLastSegment->next = newSegment;
        currentLastSegment = newSegment;
    }
}

void *malloc(u64 size){

    if(size % 8 != 0)size += 8 - (size % 8);

    MemorySegmentDescriptor *currentSegment = firstMemorySegment;
    char c;
    while (currentSegment->size < size || currentSegment->free == 0)
    {
        // clearScreen((u64)currentSegment->next == 0 ? 0x0f : 0x01);

        if ((u64)currentSegment->next == 0) {
            clearScreen(0x1);
            return 0;
        }

        currentSegment = currentSegment->next;
    }
    
    if (currentSegment->size == size)
    {
        currentSegment->free = 0;
        return (void *)(currentSegment+1);
    }

    MemorySegmentDescriptor* newSegment = (MemorySegmentDescriptor*) (((void*)(currentSegment+1)) + size);
    newSegment->size = currentSegment->size - size - sizeof(MemorySegmentDescriptor);
    newSegment->next = currentSegment->next;
    newSegment->previous = currentSegment;
    newSegment->free = 1;

    currentSegment->next = newSegment;
    currentSegment->size = size;
    currentSegment->free = 0;

    return (currentSegment+1);
}

void *calloc(u64 size, u64 value){
    if(size % 8 != 0) size += 8 - (size % 8);

    u64* location = malloc(size);

    for (int i = 0; i < size/8; i++)
    {
        *location = value;
        location++;
    }
    

}

void free(void *mallocVal){
    MemorySegmentDescriptor *currentSegment = ((MemorySegmentDescriptor*)mallocVal)-1;
    currentSegment->free = 1;

    if((currentSegment->next) == (MemorySegmentDescriptor*)((void*)(currentSegment+1))+currentSegment->size && currentSegment->next->free != 0){
        currentSegment->size += currentSegment->next->size;
        currentSegment->next = currentSegment->next->next;
        currentSegment->next->previous = currentSegment;
    }
}