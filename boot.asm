[org 0x7c00]

mov [BOOT_DRIVE], dl

;clc

;reads from Disk
NUMSECTORS equ 32
LOADTO equ 0x8000
mov ah, 0x02
mov al, NUMSECTORS
mov bx, LOADTO
mov ch, 0x00
mov cl, 0x02
mov dh, 0x00
mov dl, [BOOT_DRIVE]
int 0x13

jnc Error16

; Detecting memory

; sets VGA Graphics Mode
mov ah, 0x00
mov al, 0x13
int 0x10

cli

;enables A20 Line
in al, 0x92
or al, 2
out 0x92, al

;loads GDT
lgdt [GDT.info]

;enables PE bit
mov eax, cr0
or al, 1
mov cr0, eax

jmp codeSeg:PMode

Error16:
    mov ah, 0x0e
    mov al, 'E'
    int 0x10
    jmp $

BOOT_DRIVE: db 0

%include "gdt.asm"

[bits 32]

PMode:
    mov ax, dataSeg
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x090000
    mov esp, ebp

    ; Longmode Tutorial on wiki.osdev.org

    pushfd
    pop eax

    mov ecx, eax

    xor eax, 1 << 21

    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    xor eax, ecx
    jz NOCPUID

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz NOLONGMODE

    mov edi, 0x1000             ; Set the destination index to 0x1000.
    mov cr3, edi                ; Set control register 3 to the destination index.

    mov dword [edi], 0x2003      ; Set the uint32_t at the destination index to 0x2003.
    add edi, 0x1000              ; Add 0x1000 to the destination index.
    mov dword [edi], 0x3003      ; Set the uint32_t at the destination index to 0x3003.
    add edi, 0x1000              ; Add 0x1000 to the destination index.
    mov dword [edi], 0x4003      ; Set the uint32_t at the destination index to 0x4003.
    add edi, 0x1000              ; Add 0x1000 to the destination index.

    mov ebx, 0x00000003          ; Set the B-register to 0x00000003.
    mov ecx, 512                 ; Set the C-register to 512.
 
    .SetEntry:
        mov dword [edi], ebx     ; Set the uint32_t at the destination index to the B-register.
        add ebx, 0x1000          ; Add 0x1000 to the B-register.
        add edi, 8               ; Add eight to the destination index.
    loop .SetEntry               ; Set the next entry.

    mov eax, cr4                 ; Set the A-register to control register 4.
    or eax, 1 << 5               ; Set the PAE-bit, which is the 6th bit (bit 5).
    mov cr4, eax                 ; Set control register 4 to the A-register.

    mov ecx, 0xC0000080          ; Set the C-register to 0xC0000080, which is the EFER MSR.
    rdmsr                        ; Read from the model-specific register.
    or eax, 1 << 8               ; Set the LM-bit which is the 9th bit (bit 8).
    wrmsr                        ; Write to the model-specific register.

    mov eax, cr0                 ; Set the A-register to control register 0.
    or eax, 1 << 31              ; Set the PG-bit, which is the 32nd bit (bit 31).
    mov cr0, eax                 ; Set control register 0 to the A-register.

    mov [0xb8000], byte 'C'
    
    mov [GDT.code + 6], byte 10101111b
    mov [GDT.data + 6], byte 10101111b
    
    
    jmp codeSeg:LongMode

NOCPUID:
NOLONGMODE:
Error32:
    mov [0xb8000], byte 'E'
    jmp $


[bits 64]

LongMode:
    mov edi, 0xb8000
    mov rax, 0x1f201f201f201f20
    mov ecx, 500
    rep stosq
    jmp LOADTO

times 510-($-$$) db 0
dw 0xaa55