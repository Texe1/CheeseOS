#include "headers/IDT.h"

extern IDT _idt[256];

extern u64 isr1;

extern void LOADIDT();

void IDTInit(){
    for (u64 i = 0; i < 256; i++)
    {
        _idt[i].zero = 0x00;
        _idt[i].selector = 0x08;
        _idt[i].offset_low = (u16)((u64)&isr1 & 0x000000000000ffff);
        _idt[i].offset_mid = (u16)(((u64)&isr1 & 0x00000000ffff0000) >> 16);
        _idt[i].offset_high = (u32)(((u64)&isr1 & 0xffffffff00000000) >> 32);
        _idt[i].ist = 0x00;
        _idt[i].typesAttr = 0x8e;
    }

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);

    LOADIDT();
    
}

void keyboardHandler(){
    ((char*)0xa0000)[0] = inb(0x60);
    outb(0x20, 0x20);
    outb(0x20, 0x20);
}