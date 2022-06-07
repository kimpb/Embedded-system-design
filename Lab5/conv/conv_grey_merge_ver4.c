#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define LW_BRIDGE_SPAN 0x00005000
#define LW_BRIDGE_BASE 0xFF200000
#define CONV_MODULE_BASE 0
#define FILE_SIZE 256

void conv_c(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3], unsigned char out_img[FILE_SIZE][FILE_SIZE]);
void conv_v(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3], unsigned char out_img[FILE_SIZE][FILE_SIZE]);
// char fast_conv(char a[3][3], char b[3][3]);
static volatile char * conv_module_accel;

int main()
{
	unsigned char in_img[256][256];
	unsigned char out_img1[256][256];
    unsigned char out_img2[256][256];
    char filter[3][3] = {{-1,0,1}, {-2,0,2},{-1,0,1}};
	char in_name[64]="Lena.raw";
    int fd;
    void *lw_virtual;
    clock_t start1, end1, start2, end2;
    float res1, res2;
    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    lw_virtual = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    conv_module_accel = (volatile char*) (lw_virtual + CONV_MODULE_BASE);

	FILE* fpi;
	fpi = fopen(in_name, "rb");
	if (fpi == NULL) {
		printf("File %s open failure!!\n", in_name);
		exit(0);
	}
	// write image file(img_name) in bit mode
	fread(in_img, 256 * 256, sizeof(unsigned char), fpi);
    start1 = clock();
    conv_c(in_img, filter, out_img1);
    end1 = clock();
    start2 = clock();
    conv_v(in_img, filter, out_img2);
    end2 = clock();
	fclose(fpi);
    close(fd);
    res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
    res2 = (float)(end2 - start2) / CLOCKS_PER_SEC;
    printf("convolution with c : %.4f\n", res1);
    printf("convolution with accel : %.4f\n", res2);
}

void conv_c(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3], unsigned char out_img[FILE_SIZE][FILE_SIZE]){
    unsigned char sampling[3][3];
    char out_name[64] = "conv_c_image.raw";
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
    fpo = fopen(out_name, "wb");
	if (fpo == NULL) {
		printf("File %s open failure!!\n", out_name);
		exit(0);
	}
    fwrite(out_img, 256 * 256, sizeof(unsigned char), fpo);
    fclose(fpo);
}
void conv_v(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3], unsigned char out_img[FILE_SIZE][FILE_SIZE]){
    char out_name[64] = "conv_v_image.raw";
    int height = FILE_SIZE, width=FILE_SIZE;
	int i, j;
	int u, v;
    FILE *fpo;
    for (j = 0; j < 3; j++){
        for (i = 0; i < 3; i++){
            *(conv_module_accel + 9 + 3 * j + i) = filter[j][i];
        }
    }

    for (j = 0; j < height; j++){
        for (i = 0; i < width; i++){
            if (i == 0 || i == width-1 || j == 0 || j == height - 1){
                out_img[j][i] = 0;
                continue;
            }
            for(u = -1; u <= 1; u++){
                for(v = -1; v <= 1; v++){
                    *(conv_module_accel + 3 * (u+1) + v+1) = image[j+u][i+v];
                }
            }
            out_img[j][i] = *(conv_module_accel + 18);

            // out_img[j][i] = fast_conv(sampling, filter);
        }
        
    }
    fpo = fopen(out_name, "wb");
	if (fpo == NULL) {
		printf("File %s open failure!!\n", out_name);
		exit(0);
	}
    fwrite(out_img, 256 * 256, sizeof(unsigned char), fpo);
    fclose(fpo);
}

// char fast_conv(char a[3][3], char b[3][3]){
//     *conv_module_accel = a;
//     for (int i = 0; i < 9; i++)
//     *(conv_module_accel + 9) = b;
//     return *(conv_module_accel + 18);
// }