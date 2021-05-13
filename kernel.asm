jmp main

times 24*10 db 0

[bits 64]
[extern _start]

%include "idt.asm"

main:
call _start
jmp $