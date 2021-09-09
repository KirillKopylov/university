.386
.model flat, stdcall

.data			;c + 3ad - e/b
result dq ?		;результат
item_a dd 3		;номер по списку
item_b dd 16	;номер учебной группы
item_c dd 96	;две последние цифры года рождения
item_e dd 1996	;четыре цифры года рождения
item_d dd 2109	;день и месяц рождения

.code
main:
	finit
	fild dword ptr 	[item_a]
	fimul dword ptr [item_a]
	fimul dword ptr [item_d]	;st(0) -> 3ad
	fild dword ptr 	[item_e]
	fild dword ptr 	[item_b]
	fdiv 						;st(0) -> e/b
	fild dword ptr 	[item_c]
	fadd st, st(2) 				;st(0) -> c + 3ad
	fsub st, st(1) 				;st(0) -> c + 3ad - e/b -> 18925.25
	fstp dword ptr 	[result] 	;st(0) -> memory
	
end main
