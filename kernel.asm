jmp main



[bits 64]
[extern _start]

%include "idt.asm"

main:
call _start
jmp $