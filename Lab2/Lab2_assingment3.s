
.global recursive_sum
recursive_sum:
        push    {r4, fp, lr}
        add     fp, sp, #8
        sub     sp, sp, #12
        str     r0, [fp, #-16]
        ldr     r3, [fp, #-16]
        cmp     r3, #1
        bgt     0x24
        mov     r3, #1
        b       0x50
        ldr     r3, [fp, #-16]
        sub     r3, r3, #1
        mov     r0, r3
        bl      0
        mov     r4, r0
        ldr     r3, [fp, #-16]
        sub     r3, r3, #2
        mov     r0, r3
        bl      0
        mov     r3, r0
        add     r3, r4, r3
        mov     r0, r3
        sub     sp, fp, #8
        pop     {r4, fp, pc}



/*
recursive_sum:
        cmp r0, #1
        movle r0, #1
        movle pc, lr

        sub sp, sp, #8
        str r0, [sp, #0]
        str lr, [sp, #4]



        bl recursive_sum

        ldr r0, [sp, #0]
        ldr lr, [sp, #4]

        ldr r1, [sp, #8]
        ldr r2, [sp, #16]

        add sp, sp, #8

        add r0, r1, r2
        
        bx lr

*/
/*
        mov r1, #1
        mov r2, #1
        mov r3, #2
loop:
        cmp r3, #15
        bgt end
        add r0, r2, r1
        mov r1, r2
        mov r2, r0
        add r3, r3, #1
        b loop

end:    bx lr 
*/