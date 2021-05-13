#include "headers/IO.h"
#include "headers/String.h"
#include "headers/IDT.h"


char *videoMem = (char*)0xa0000;

void _start(){
    videoMem[0] = 0xf;
    IDTInit();
    return;
}