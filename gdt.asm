GDT:
    .null:
        dq 0
    .code:
        dw 0xffff
        dw 0x0000
        db 0x00
        db 10011010b
        db 11001111b
        db 0x00
    .data:
        dw 0xffff
        dw 0x0000
        db 0x00
        db 10010010b
        db 11001111b
        db 0x00
    .info:
        dw GDT.info - GDT - 1
        dq GDT

codeSeg equ GDT.code - GDT
dataSeg equ GDT.data - GDT

[bits 32]

EditGDT:
    mov [GDT.code + 6], byte 10101111b
    mov [GDT.data + 6], byte 10101111b
ret 

[bits 16]