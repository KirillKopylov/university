global _start

section .data
x dq 20
y dq 24
z dq 0
section .global
_start:
    
    mov rax, [x]
    mov rbx, [y]
    add rax, rbx
    mov r8, rax ;r8 -> x+y
    mov rax, [y]
    mul rax
    mov rbx, 4
    mul rbx
    mov r9, rax ;r9 -> 4*y^2
    mov rax, [x]
    mul rax ;rax -> x^2
    sub r9, rax
    mov rax, r9
    mov rbx, 10
    mul rbx ;rax -> 10*(4*y^2-x^2)
    mov rbx, r8
    div rbx
    mov [z], rax
