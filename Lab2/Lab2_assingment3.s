
.global recursive_sum

recursive_sum:
        mov r0, #1
        mov r1, #1
        mov r3, #2
check_zero:
        cmpgt r3, #15
        beq end
        add r3, r3, #1
        add r2, r0, r1
        mov r0, r1
        mov r1, r2
        b check_zero

end:    mov r0, r2
        bx lr