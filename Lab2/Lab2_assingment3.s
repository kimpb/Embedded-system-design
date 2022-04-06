
.global recursive_sum

recursive_sum:
        mov r0, #1
        mov r1, #1
<<<<<<< HEAD
        mov r3, #15
check_zero:
        cmp r3, #2
        beq end
        sub r3, r3, #1
=======
        mov r3, #2
check_zero:
        cmpgt r3, #15
        beq end
        add r3, r3, #1
>>>>>>> d6ca7b38eaa6d8aaf1e1ee5cf926570f80864ad4
        add r2, r0, r1
        mov r0, r1
        mov r1, r2
        b check_zero

end:    mov r0, r2
        bx lr