#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define LW_BRIDGE_SPAN 0x00005000
#define LW_BRIDGE_BASE 0xFF200000
#define CONV_MODULE_BASE 0
#define FILE_SIZE 256

void conv_c(char image[FILE_SIZE][FILE_SIZE], char filter[3][3], char out_img[FILE_SIZE][FILE_SIZE]);
void conv_v(char image[FILE_SIZE][FILE_SIZE], char filter[3][3], char out_img[FILE_SIZE][FILE_SIZE]);
char fast_conv(char a[3][3], char b[3][3]);
static volatile char * conv_module_accel;

int main()
{
	char in_img[256][256];
	char out_img[256][256];
    char filter[3][3] = {{-1,0,1}, {-2,0,2},{-1,0,1}};
	char in_name[64]="Lena.raw", out_name[64]="lena_conv_ver2.raw";
    int fd;
    void *lw_virtual;
    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    lw_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    conv_module_accel = (volatile char*) (lw_virtual + CONV_MODULE_BASE);

	FILE* fpi, * fpo;
	fpi = fopen(in_name, "rb");
	if (fpi == NULL) {
		printf("File %s open failure!!\n", in_name);
		exit(0);
	}
	// write image file(img_name) in bit mode
	fpo = fopen(out_name, "wb");
	if (fpo == NULL) {
		printf("File %s open failure!!\n", out_name);
		exit(0);
	}
	fread(in_img, 256 * 256, sizeof(unsigned char), fpi);
    conv_c(in_img, filter, out_img);
    conv_v(in_img, filter, out_img);
	fclose(fpi);
    close(fd);
}

void conv_c(char image[FILE_SIZE][FILE_SIZE], char filter[3][3], char out_img[FILE_SIZE][FILE_SIZE]){
    char sampling[3][3];
    int sum = 0;
    int height = FILE_SIZE, width=FILE_SIZE;
	int i, j;
	int u, v;
    FILE *fpo;

    for (j = 0; j < height; j++){
        for (i = 0; i < width; i++){
            sum = 0;
            if (i == 0 || i == width-1 || j == 0 || j == height - 1){
                out_img[j][i] = 0;
                continue;
            }
            for(u = -1; u <= 1; u++){
                for(v = -1; v <= 1; v++){
                    sampling[u+1][v+1] = image[j+u][i+v];
                }
            }
            for(u = 0; u < 3; u++){
                for(v = 0; v < 3; v++){
                    sum += (int)sampling[u][v] * (int)filter[u][v];
                }
            }
            if (sum < 0){
                sum = 0;
            }
            else if(sum > 255){
                sum = 255;
            }
            out_img[j][i] = (unsigned char)(sum & 0xFF);
        }
        
    }
    fpo = fopen("conv_c.raw", "wb");
    fwrite(out_img, 256 * 256, sizeof(unsigned char), fpo);
    fclose(fpo);
}
void conv_v(char image[FILE_SIZE][FILE_SIZE], char filter[3][3], char out_img[FILE_SIZE][FILE_SIZE]){
    char sampling[3][3];
    int sum = 0;
    int height = FILE_SIZE, width=FILE_SIZE;
	int i, j;
	int u, v;
    FILE *fpo;

    for (j = 0; j < height; j++){
        for (i = 0; i < width; i++){
            sum = 0;
            if (i == 0 || i == width-1 || j == 0 || j == height - 1){
                out_img[j][i] = 0;
                continue;
            }
            for(u = -1; u <= 1; u++){
                for(v = -1; v <= 1; v++){
                    sampling[u+1][v+1] = image[j+u][i+v];
                }
            }

            out_img[j][i] = fast_conv(sampling, filter);
        }
        
    }
    fpo = fopen("conv_v.raw", "wb");
    fwrite(out_img, 256 * 256, sizeof(unsigned char), fpo);
    fclose(fpo);
}

char fast_conv(char a[3][3], char b[3][3]){
    *conv_module_accel = a;
    *(conv_module_accel + 9) = b;
    return *(conv_module_accel + 18);
}