
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include"address_map_arm.h"

int SEG7_CODE(int i){
    char BIT_CODE[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111};
        return BIT_CODE[i];
}

int main(void){
    int fd;
    void *lw_virtual;
    volatile int *hex30;
    volatile int *hex54;
    int SEGMENT7;
    int hex[5] = {0};


    int student_id[20] = {2, 0, 1, 5, 1, 2, 4, 2, 1, 3, 2, 0, 1, 7, 1, 2, 4, 1, 7, 8};

    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    lw_virtual = mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    hex30 = (volatile int *) (lw_virtual + HEX3_HEX0_BASE);
    hex54 = (volatile int *) (lw_virtual + HEX5_HEX4_BASE);

    *hex30 = 0;
    *hex54 = 0;
    int i;
    for(i=0;;i++){
        SEGMENT7 = SEG7_CODE(student_id[i%20]);

        *hex54 = *hex54 << 8;
        *hex54 = (*hex54) | (((*hex30) & 0x7F000000) >> 24);

        *hex30 = *hex30 << 8;
        *hex30 = (*hex30) | SEGMENT7;


        usleep(1000000);

    }

    munmap(lw_virtual, LW_BRIDGE_BASE);
    close(fd);

    return 0;

}