
#include <stdio.h>
#include <math.h>
#include <iostream>
#define M_PI 3.141592
#define C(u) ((u)==0 ? (1/sqrt(2)) : 1)
#define min(x, y) ((x)>(y) ? (y) : (x))
#define abs(x) ((x)>0 ? (x) : (-x))
#define max(x, y) ((x)>(y) ? (x) : (y))
int main()
{
	unsigned char in_img[256][256];
	unsigned char out_img[256][256];
	char in_name[256], out_name[256];
	//int iblk[8][8], oblk[8][8];
	double oblk[256][256], tmp, max_tmp;
	int i, j;
	int u, v;
	FILE* fpi, * fpo;
	printf("Input an image file name to process: ");
	scanf_s("%s", in_name, 256);
	printf("Input an output image file name to save: ");
	scanf_s("%s", out_name, 256);
	// read image file(img_name) in bit mode
	fopen_s(&fpi, in_name, "rb");
	if (fpi == NULL) {
		printf("File %s open failure!!\n", in_name);
		exit(0);
	}
	// write image file(img_name) in bit mode
	fopen_s(&fpo, out_name, "wb");
	if (fpo == NULL) {
		printf("File %s open failure!!\n", out_name);
		exit(0);
	}
	fread(in_img, 256 * 256, sizeof(unsigned char), fpi);
	for (u = 0; u < 256; u++)
		for (v = 0; v < 256; v++) {
			tmp = 0;
			for (i = 0; i < 256; i++)
				for (j = 0; j < 256; j++)
					tmp += cos((2 * i + 1) * u * M_PI / (2 * 256)) * cos((2 * j + 1) * v * M_PI / (2 * 256)) *
					in_img[i][j];
			if (u == 0 & v == 0)
				oblk[u][v] = tmp / 256;
			else if (u == 0 || v == 0)
				oblk[u][v] = sqrt(2) * tmp / 256;
			else
				oblk[u][v] = 2 * tmp / 256;
		}
	max_tmp = 0;
	for (u = 0; u < 256; u++)
		for (v = 0; v < 256; v++)
			max_tmp = max(max_tmp, abs(oblk[u][v]));
	for (u = 0; u < 256; u++)
		for (v = 0; v < 256; v++)
			out_img[u][v] = min((int)(abs(oblk[u][v]) / max_tmp * 4096 * 2), 255);
	fwrite(out_img, 256 * 256, sizeof(unsigned char), fpo);
	fclose(fpi);
	fclose(fpo);
}