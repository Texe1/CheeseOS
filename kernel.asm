jmp main

global MEMORYREGIONCOUNT
MEMORYREGIONCOUNT:
db 0

global MEMORYREGIONDESCRIPTORS 
MEMORYREGIONDESCRIPTORS:
times 24*20 db 0

[bits 64]
[extern _start]
;%include "chars.asm"

main:
call _start
jmp $

%include "idt.asm"