
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include"address_map_arm.h"

#define OFFSET 0xFFFFFF

int main(void){
    int fd;
    void *t1, *t2, *t3, *t4, *t5;
    volatile int *t6;

    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    t1 = mmap (NULL, 1, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, 0xd4dd3140);
    t2 = mmap (NULL, 1, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, 0xf04f4140);
    t3 = mmap (NULL, 1, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, 0xf04f3000);
    t4 = mmap (NULL, 1, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, 0xf04fe000);
    t5 = mmap (NULL, SDRAM_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, SDRAM_BASE);
    t6 = (volatile int *) t5 + OFFSET;

    // printf("%x, %x, %x, %x\n", t3, t4, t5, t6);
    printf("t6 : %x\n", t6);

    while(1){
        printf("%x\n", *t6);
        // printf("%x, %x, %x, %x\n", *t3, *t4, *t5, *t6);
        usleep(10000);
    }
    // printf("%x, %x\n", *t3, *t4);
}