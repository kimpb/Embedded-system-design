#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define FILE_SIZE 256

void conv_c(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3]);

int main()
{
	unsigned char in_img[256][256];
    char filter[3][3] = {{-1,0,1}, {-2,0,2},{-1,0,1}};
	char in_name[64]="Lena.raw";
    
    clock_t start1, end1, start2, end2;
    float res1, res2;
    
	FILE* fpi;
	fpi = fopen(in_name, "rb");
	if (fpi == NULL) {
		printf("File %s open failure!!\n", in_name);
		exit(0);
	}
	// write image file(img_name) in bit mode
	fread(in_img, 256 * 256, sizeof(unsigned char), fpi);
    start1 = clock();
    conv_c(in_img, filter);
    end1 = clock();
	fclose(fpi);
    res1 = (float)(end1 - start1) / CLOCKS_PER_SEC;
    printf("convolution with c : %.4f\n", res1);
}

void conv_c(unsigned char image[FILE_SIZE][FILE_SIZE], char filter[3][3]){
    unsigned char out_img[256][256];
    char sampling[3][3];
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
