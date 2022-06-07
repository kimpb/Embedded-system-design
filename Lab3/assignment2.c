
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include"address_map_arm.h"

int SEG7_CODE(int i){
    char BIT_CODE[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111};
        return BIT_CODE[i];
}
int SEG7_OPERATOR(int i){
    char BIT_CODE[4] = {0b1110000, 0b1000000, 0b1110110, 0b1010010};
    return BIT_CODE[i]; 
}

int main(void){
    int fd;
    void *lw_virtual;
    volatile int *hex30;
    volatile int *hex54;
    volatile int *key;
    int status = 0, operand1 = 0, operand2 = 0, operator = 0, result = 0;

    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    lw_virtual = mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    hex30 = (volatile int *) (lw_virtual + HEX3_HEX0_BASE);
    hex54 = (volatile int *) (lw_virtual + HEX5_HEX4_BASE);
    key = (volatile int *) (lw_virtual + KEY_BASE);

    *hex30 = 0;
    *hex54 = 0;
    int pressed1 = 0, pressed2 = 0;
    while(1){
        pressed1 = 0;
        pressed2 = 0;
        while((*key & 0b0001 | *key & 0b0010)){
            if(*key & 0b1)
            pressed1 = 1;
            if(*key & 0b10)
            pressed2 = 1;
        }
        if(pressed1){
            switch(status%4){
                case 0:
                operand1 = operand1 + 1;
                break;

                case 1:
                operator = operator + 1;
                break;

                case 2:
                operand2 = operand2 + 1;
                break;

                case 3:
                operand1 = 0;
                operand2 = 0;
                operator = 0;
                break;
            }
        }
        if(pressed2){
            status = status + 1;
        }
        if (status%4 == 3){
            switch(operator%4){
                case 0:
                result = (operand1%10) + (operand2%10);
                break;
                case 1:
                result = (operand1%10) - (operand2%10);
                break;
                case 2:
                result = (operand1%10) * (operand2%10);
                break;
                case 3:
                result = (operand1%10) / (operand2%10);
                break;
            }
        }
        *hex30 = SEG7_OPERATOR(operator%4) << 24 |  SEG7_CODE(operand2%10) << 16 | (0b1001000) << 8 | SEG7_CODE(result%10);
        *hex54 = SEG7_CODE(operand1%10);
        usleep(1000);

    }

    munmap(lw_virtual, LW_BRIDGE_BASE);
    close(fd);

    return 0;
}