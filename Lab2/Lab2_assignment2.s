
.global sum1to1000

sum1to1000:
        mov r2, #0
        mov r1, #1
loop:
        add r2, r2, r1
        add r1, r1, #1
        cmp r1, r0
        bgt end
        b   loop

end:    mov r0, r2
        bx lr
        