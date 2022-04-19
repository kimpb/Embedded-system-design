
.global hamming_distance
hamming_distance:
        eor r0, r1, r0
        mov r2, #0
        mov r3, #0
loop:
        cmp r0, #0
        beq end
        and r2, r0, #1
        cmp r2, #0
        beq skip
        add r3, r3, #1
skip:   lsr r0, r0, #1
        b   loop

end:    mov r0, r3
        bx  lr
