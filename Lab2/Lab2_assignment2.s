
.global sum1to1000

sum1to1000:
<<<<<<< HEAD
        mov r0, #1000
        mov r1, r0
check_zero:
        cmp r1, #0
=======
        mov r0, #1
        mov r1, r0
check_zero:
        cmpgt r1, #1000
>>>>>>> d6ca7b38eaa6d8aaf1e1ee5cf926570f80864ad4
        beq end
        sub r1, r1, #1
        add r0, r0, r1
        b   check_zero

end:    bx lr
        