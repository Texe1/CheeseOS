#include "./IO.c"
#include "./headers/String.h"

void setCursor(unsigned short pos){
    outb(0x3d4, 0x0f);
    outb(0x3d5, (unsigned char)(pos & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (unsigned char) ((pos >> 8) & 0xff));
}



unsigned short getCursor(){
    unsigned short pos;
    
    outb(0x3d4, 0x0f);
    pos |= inb(0x3d5);
    outb(0x3d4, 0x0e);
    pos |= ((unsigned short)inb(0x3d5)) << 8;
    
    return pos;
}

void moveCursor(int digits){
    setCursor(getCursor()+digits);
}

char *videoMem = (char*)0xb8000;

char color = 0x0f;

void logStr(str *s){

    unsigned short pos = getCursor();

    for (int i = 0; i < s->length; i++)
    {
        videoMem[2*(pos+i)] = s->addr[i];
    }
    
}

void setScreenColor(char fgcolor, char bgcolor){
    color = ((bgcolor & 0x0f) << 4) | (fgcolor & 0xf);
    for (int i = 0; i < 25*80; i++)
    {
        videoMem[2*i+1] = color;
    }
    
}

void _start(){
    setScreenColor(0xf, 0x0);

    *testStr = constructStr("CheeseOS bootloader did succesfully load the kernel!");

    setCursor(0);

    logStr(testStr);
    return;
}