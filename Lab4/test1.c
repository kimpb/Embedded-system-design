
/* assignment1.c */

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
    int cnt = 0;
    int status = 0, operand1 = 0, operand2 = 0, operator = 0, result = 0; // 변수 선언 및 초기화

    int pressed1 = 0, pressed2 = 0; // push button flag를 위한 변수 선언
    
    FILE *key = fopen("/dev/key", "r");
    FILE *hex30 = fopen("/dev/hex30", "w");
    FILE *hex54 = fopen("/dev/hex54", "w"); // device driver open
    while(1){
        pressed1 = 0; //Initialize flag for Push Button
        pressed2 = 0;
        buffer = fgetc(key); // fgetc 함수를 통해 key값 읽어옴
        while(buffer){ //while loop for prevent bouncing issue
            if(buffer & 0b1){ // KEY0가 눌렸을 때
            pressed1 = 1;
            break;
            }
            else if(buffer & 0b10){ // KEY1이 눌렸을 때
            pressed2 = 1;
            break;
            }
        }
        rewind(key); // rewind function을 통해 파일 포인터 초기화
        if(pressed1){ // KEY0가 눌렸을 때,
            switch(status%4){ // 현재 status에 따른 switch case문
                case 0:
                operand1 = operand1 + 1; // Increase operand1 at status0
                break;

                case 1:
                operator = operator + 1; // change operator at status1
                break;

                case 2:
                operand2 = operand2 + 1; // Increase operand2 at status2
                break;

                case 3: // Initialize operand and operator
                operand1 = 0;
                operand2 = 0;
                operator = 0;
                break;
            }
        }
        if(pressed2){ //KEY1이 눌렸을 때,
            status = status + 1; // Increase status
        }
        if (status%4 == 3){ // 현재 status가 3이면,
            switch(operator%4){ // 연산자에 따라 계산을 달리하기 위한 switch case문
                case 0:
                result = (operand1%10) + (operand2%10); // add
                break;
                case 1:
                result = (operand1%10) - (operand2%10); // sub
                break;
                case 2:
                result = (operand1%10) * (operand2%10); // mul
                break;
                case 3:
                result = (operand1%10) / (operand2%10); //divide
                break;
            }
        }
        
        hex30_temp = SEG7_OPERATOR(operator%4) << 24 |  SEG7_CODE(operand2%10) << 16 | (0b1001000) << 8 | SEG7_CODE(result%10); 
// HEX3에는 operator가, HEX2에는 operand2, HEX1에는 =, HEX0에는 result를 표시
        hex54_temp = SEG7_CODE(operand1%10); // HEX4에는 operand1을 표시한다.

            
        fwrite(&hex30_temp, sizeof(int), 1, hex30);
        fflush(hex30);
        fwrite(&hex54_temp, sizeof(int), 1, hex54);
        fflush(hex54);
        usleep(100); // 1ms동안 delay

    }
}
