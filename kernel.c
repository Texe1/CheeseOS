#include "headers/IO.h"
#include "headers/String.h"
#include "headers/IDT.h"
#include "headers/screen.h"
#include "headers/memory.h"


char *videoMem = (char*)0xa0000;

void _start(){
    videoMem[0] = 0xf;
    IDTInit();
    char c = 0;
    clearScreen(0xf);
    
    return;
}