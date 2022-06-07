
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>
#include "address_map_arm.h"

#define OFFSET 0xFFFFFF

int SEG7_CODE(int i){
    char BIT_CODE[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111};
        return BIT_CODE[i];
}

int main(void){
    int fd;
    void *SDRAM_virtual;
    volatile int *flag_ptr;
    int SEGMENT7;
    int hex30_temp = 0, hex54_temp = 0;
    int flag;
    bool dir = 1;

    FILE *hex30 = fopen("/dev/hex30", "w");
    FILE *hex54 = fopen("/dev/hex54", "w");

    int student_id[20] = {2, 0, 1, 5, 1, 2, 4, 2, 1, 3, 2, 0, 1, 7, 1, 2, 4, 1, 7, 8};
    

    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    SDRAM_virtual = mmap (NULL, SDRAM_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, SDRAM_BASE);
    
    flag_ptr = (volatile int *) (SDRAM_virtual + OFFSET);

    flag = *flag_ptr;
    
    int i = 0;
    while(1){
        flag = *flag_ptr;
        if(flag){
            printf("interrupt!\n");
            if(!dir){
                i = i + 7; 
            }
            else{
                i = i - 7;
            }
            dir = !dir;
            *flag_ptr = 0;
        }
        if(dir){
            SEGMENT7 = SEG7_CODE(student_id[i%20]);
            hex54_temp = (hex54_temp << 8) | (((hex30_temp) & 0x7F000000) >> 24); 
            // 왼쪽으로 shift한 HEX54와 HEX3에 출력되는 값 합친 후 HEX54 출력
            hex30_temp = (hex30_temp << 8) | (SEGMENT7 & 0xFF); 
            // 왼쪽으로 shift한 HEX30에 SEGMENT7 변수 합쳐 HEX30에 출력
            i++;
        }
        else{
            SEGMENT7 = SEG7_CODE(student_id[i%20]);
            hex30_temp = (hex30_temp >> 8) | ((hex54_temp & 0xFF) << 24);
            hex54_temp = (hex54_temp >> 8) | ((SEGMENT7 & 0xFF) << 8);
            i--;
        }
        if(i < 8){
            i = i + 20;
        }
        
        fwrite(&hex54_temp, sizeof(int), 1, hex54);
        fflush(hex54);
        fwrite(&hex30_temp, sizeof(int), 1, hex30);
        fflush(hex30);
        usleep(200000);

    }

    fclose(hex30);
    fclose(hex54);
    close(fd);

    return 0;

}