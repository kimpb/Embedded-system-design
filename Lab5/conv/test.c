#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define LW_BRIDGE_SPAN 0x00005000
#define LW_BRIDGE_BASE 0xFF200000
#define CONV_MODULE_BASE 0

static volatile char * conv_module_accel;

char fast_conv(char a[3][3], char b[3][3]){
    *conv_module_accel = a;
    *(conv_module_accel + 9) = b;
    return *(conv_module_accel + 18);
}


int main(void){
    int fd;
    void *lw_virtual;
    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    lw_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    conv_module_accel = (volatile char*) (lw_virtual + CONV_MODULE_BASE);

    
    char a [3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    char b [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    char c;

    c = fast_conv(a, b);

    printf("%d\n", c);



}
