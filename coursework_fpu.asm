global _start

section .data
x dd 20
y dd 24
a dd 8
temp4 dd 4
temp10 dd 10

section .global
_start:
    fild    dword [x]
    fild    dword [y]
    fadd                    ;st0 -> x+y
    fild    dword [y]
    fimul   dword [y]
    fimul   dword [temp4]   ;4*y^2 -> st0
    fistp   dword [temp4]   ;4*y^2 -> temp4
    fild    dword [x]
    fimul   dword [x]
    fild    dword [temp4]
    fsub    st0, st1        ;st0 -> 4*y^2-x^2
    fimul   dword [temp10]  ; st0 -> 10*(4y^2 - x^2)
    fild    dword [x]
    fild    dword [y]
    fadd                    ;st0 -> x+y
    fdiv    st1, st0        ;st1 -> 10*(4*y^2-x^2)/(x+y)
    fldlg2                  ;st0 -> log10(2)
    fild    dword [a]       ;st1 -> a
    fyl2x
    
