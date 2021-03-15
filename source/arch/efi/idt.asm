bits 64

section .text

%include "cpu/common.asm"

extern host_interrupt_handler

common_interrupt_handler:
    pushaq
    mov rcx, rsp
    sub rsp, 20h
    call host_interrupt_handler
    add rsp, 20h
    popaq

    add rsp, 10h
    iretq

%assign index 0

%macro interrupt_stub_no_err 1
    push 0
    push %1
    jmp common_interrupt_handler
    %assign index index+1
%endmacro

%macro interrupt_stub_err 1
    nop
    nop
    push %1
    jmp common_interrupt_handler
    %assign index index+1
%endmacro

global interrupt_handlers
interrupt_handlers:
    %rep 8
        interrupt_stub_no_err index
    %endrep

    nop
    nop

    %rep 5
        nop
    %endrep

    %rep 2
        nop
    %endrep

    nop

    %rep 238
        nop
    %endrep