/* recursive_sum.s */
.global recursive_sum /* recursive_sum 함수를 외부로 노출시킴 */
        
recursive_sum:
        str lr, [sp, #-4]! /* link register(return address) stack에 push */
        str r4, [sp, #-4]! /* 중간 계산값을 저장하는 register r4를 stack에 push */
        str r0, [sp, #-4]! /* input값이 저장 되어있는 register r0를 stack에 push */
        cmp r0, #1 
        bgt fibo /* num 이 1보다 크면 fibo로 branch */
        mov r0, #1 
        b fibo_end /* num이 1 이하면 r0에 1을 assign 하고 fibo_end로 branch 하여 r0값 return */

fibo :
        ldr r1, [sp] /* 현재 stack에 저장된 값 r1로 불러옴 */
        sub r0, r1, #1 /* r0, num을 1씩 감소시킴 */ 
        bl recursive_sum /* recursive_sum(r0 - 1) call */
        mov r4, r0 /* return된 recursive_sum(r0 - 1)값 r4에 assign */
        ldr r1, [sp] /* 현재 stack에 저장된 값 r1로 불러옴 */
        sub r0, r1, #2 /* r0, num을 2 감소시킴 */
        bl recursive_sum /* recursive_sum(r0 - 2) call */
        add r0, r0, r4 /* r0 = recursive_sum(r0 - 2) + recursive_sum(r0 - 1) */

fibo_end :
        add sp, sp, #4 /* 감소된 stack 원상복구 */
        ldr r4, [sp], #4
        ldr lr, [sp], #4 /* restore r4, lr */
        bx lr /* return */

