#include "headers/screen.h"
#include "headers/typedefs.h"

char *videoMemory = (char*)0xa0000;

u64 VGA_WIDTH =  320;
u64 VGA_HEIGHT = 200;

void clearScreen(char color){
    
    for (u64 i = 0; i < 10; i++)
    {
        for (u64 j = 0; j < VGA_HEIGHT*VGA_WIDTH/10; j++)
        {
            videoMemory[10*j+i] = color;
        }
        
    }
    
}

void Putpixel(u64 x, u64 y, char color){
    if(x < VGA_WIDTH && y < VGA_HEIGHT) videoMemory[VGA_WIDTH*y+x] = color;
}