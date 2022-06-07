#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <func1.h>
#include <sys/mman.h>

#define LW_BRIDGE_SPAN 0x00005000
#define LW_BRIDGE_BASE 0xFF200000
#define CONV_IN_IMG_BASE 0
#define CONV_IN_FILTER_BASE 9
#define CONV_OUT_IMG_BASE 18
#define FILE_SIZE 256

void conv_c(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3], unsigned char out_img[FILE_SIZE][FILE_SIZE]);
void conv_v(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3], unsigned char out_img[FILE_SIZE][FILE_SIZE]);
static volatile unsigned char *input_image;
static volatile char *input_filter;
static volatile unsigned char *output_image;

int main()
{
	unsigned char in_img[256][256];
	unsigned char out_img[256][256];
    char filter[3][3] = {{-1,0,1}, {-2,0,2},{-1,0,1}};
	char in_name[64]="Lena.raw", out_name[64]="lena_conv_ver2.raw";
    int fd;
    void *lw_virtual;
    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    lw_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE, MAP_SHARED, fd, LW_BRIDGE_BASE));
    input_image = (volatile unsigned char *)(lw_virtual + CONV_IN_IMG_BASE);
    input_filter = (volatile char *)(lw_virtual + CONV_IN_FILTER_BASE);
    output_image = (volatile unsigned char *)(lw_virtual + CONV_OUT_IMG_BASE);

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

	fwrite(out_img, 256 * 256, sizeof(unsigned char), fpo);
	fclose(fpi);
	fclose(fpo);
    close(fd);
}

void conv_c(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3], unsigned char out_img[FILE_SIZE][FILE_SIZE]){
    unsigned char sampling[3][3];
    int sum = 0;
    int height = FILE_SIZE, width=FILE_SIZE;
	int i, j;
	int u, v;

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
}
void conv_v(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3], unsigned char out_img[FILE_SIZE][FILE_SIZE]){
    unsigned char sampling[3][3];
    int sum = 0;
    int height = FILE_SIZE, width=FILE_SIZE;
	int i, j;
	int u, v;

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
            for (int j = 0; j < 3; j++){
                for (int i = 0; i < 3; i++){
                    *(input_image + 3 * j + i) = sampling[j][i];
                }
            }
            for (int j = 0; j < 3; j++){
                for (int i = 0; i < 3; i++){
                    *(input_filter + 3 * j + i) = filter[j][i];
                }
            }
            out_img[j][i] = *output_image;
        }
        
    }
}