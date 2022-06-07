#include <stdio.h>
#include <stdlib.h>

int SEG7_CODE(int i){
    char BIT_CODE[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111}; 
        return BIT_CODE[i]; // input으로 int i를 입력 받으면 i에 해당하는 7-segment code를 return하는 SEG7_CODE함수
}

int SEG7_OPERATOR(int i){
    char BIT_CODE[4] = {0b1110000, 0b1000000, 0b1110110, 0b1010010};
    return BIT_CODE[i]; 
} // input으로 int i를 입력 받으면 i에 해당하는 7-segment code를 return하는 SEG7_OPERATOR 함수


int main(int argc, char *argv[]){
    char buffer;
    int ch = 0x1;
    int hex30_temp, hex54_temp;
    int cnt = 1;
    // int temp[1] = {0b11111};
    int status = 0, operand1 = 0, operand2 = 0, operator = 0, result = 0; // 변수 선언 및 초기화
    FILE *hex30 = fopen("/dev/hex30", "w");
    FILE *hex54 = fopen("/dev/hex54", "w");
    FILE *key = fopen("/dev/key", "r");

    while(1){
        if(fgetc(key)){
            cnt++;

        }
        int temp = SEG7_CODE(cnt % 10) | (SEG7_CODE((cnt / 10)%10) << 8);
        fwrite(&temp, sizeof(int), 1, hex30);
        // fputc(SEG7_CODE((cnt/10)%10) << 8 | SEG7_CODE(cnt%10), hex30);
        // fputc(SEG7_CODE((cnt/10)%10), hex30+1);
        // fputc(SEG7_CODE((cnt/100)%10), hex30+2);
        // fputc(SEG7_CODE((cnt/1000)%10), hex30+3);
    }

    
}