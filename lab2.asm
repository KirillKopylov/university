.386
.model flat, stdcall

.data				;c + 3ad - e/b
result dd 		?

.code
main:
	mov eax, 	3
	mov ebx, 	3
	mul ebx 			;eax -> 3a
	mov ebx, 	2109
	mul ebx
	mov ecx, 	eax 	;ecx -> 3ad
	mov eax, 	1996
	mov ebx, 	16
	div ebx
	mov esi, 	eax		;esi -> e/b
	add ecx, 	96 		;ecx -> c+3ad
	sub ecx, 	esi 	;esi -> c + 3ad - e/b
	mov result, ecx 	;memory -> c + 3ad - e/b
end main