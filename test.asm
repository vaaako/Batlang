global _start
_start:
	mov rax, 60 ;; Use syscall 60 (exit) -> "move 60 to rax"
	mov rdi, 24 ;; Return 24 (maximum 255) -> "move 24 to the first argument of exit"
	syscall     ;; Exit


