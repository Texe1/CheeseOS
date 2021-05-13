[extern _idt]
idt_descriptor:
    dw 4095
    dq _idt

%macro PUSHALL 0
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11
%endmacro

%macro POPALL 0
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rax
%endmacro

[extern keyboardHandler]
GLOBAL isr1
isr1:
    PUSHALL
    call keyboardHandler
    POPALL
    iretq

GLOBAL LOADIDT
LOADIDT:
    lidt[idt_descriptor]
    sti
    ret