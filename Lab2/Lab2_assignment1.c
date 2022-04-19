#include <stdio.h>

int hamming_distance(int, int);

int main(void){
        printf("int1 : %d(0x%x), int2: %d(0x%x), hamming_distance: %d\n", 0xffffffff, 0xffffffff, 0x80000000, 0x80000000, hamming_distance(0xffffffff, 0x80000000) );
        return  hamming_distance(0xffffffff, 0x80000000);
}//adasd