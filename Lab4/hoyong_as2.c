#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h> 
#include <stdbool.h>

int SEG7_CODE(int i){
    char BIT_CODE[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111};
        return BIT_CODE[i]; // input으로 int i를 입력 받으면 i에 해당하는 7-segment code를 return하는 SEG7_CODE함수
}

int main(void){
    int SEGMENT7; // hex에 표시하기 위한 7 segment code를 저장하는 변수
    FILE *hex30 = fopen("/dev/hex30", "w");
    FILE *hex54 = fopen("/dev/hex54", "w");
    int hex30_temp = 0, hex54_temp = 0;
    int next_ledr, prev_ledr = 0;
    bool dir = 0;
    unsigned int i = 0;

    // int student_id[20] = {2, 0, 1, 5, 1, 2, 4, 2, 1, 3, 2, 0, 1, 7, 1, 2, 4, 1, 7, 8}; //학번 integer 배열 
    int student_id[20] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
    // prev_ledr = fgetc(ledr);
    // rewind(ledr);
    while(1){

        FILE *ledr = fopen("/dev/ledr", "r");
        next_ledr = fgetc(ledr);
        printf("%d\n", next_ledr);
        //rewind(ledr);
        if (i > 20){
            i = 19;
        }
        else if (i == 20){
            i = 0;
        }
        if (next_ledr != prev_ledr){
            dir = !dir;
        }
        SEGMENT7 = SEG7_CODE(student_id[i]); // student_id array의 i%20번째 요소를 7 segment로 변환 후 저장
        if (dir){
            hex54_temp = (hex54_temp << 8) | (((hex30_temp) & 0x7F000000) >> 24); // 왼쪽으로 shift한 HEX54와 HEX3에 출력되는 값 합친 후 HEX54 출력
            hex30_temp = (hex30_temp << 8) | (SEGMENT7 & 0xFF); // 왼쪽으로 shift한 HEX30에 SEGMENT7 변수 합쳐서 HEX30에 출력
            i++;
        }
        // else {
        //     hex30_temp = (hex30_temp >> 8) | ((hex54_temp & 0xFF) << 24);
        //     hex54_temp = (hex54_temp >> 8) | ((SEGMENT7 & 0xFF) << 8);
        //     i--;
        // }
        prev_ledr = next_ledr;

        fwrite(&hex54_temp, sizeof(int), 1, hex54);
        fflush(hex54);
        fwrite(&hex30_temp, sizeof(int), 1, hex30);
        fflush(hex30);
        usleep(500 * 1000); // 0.5초씩 delay
        fclose(ledr);
    }
    fclose(hex30);
    fclose(hex54);

    return 0; // 종료
}

