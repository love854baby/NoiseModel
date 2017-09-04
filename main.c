//
// Created by ye on 11/6/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define XDIM 256
#define YDIM 256
#define RADIUS 50
#define INNER 100
#define OUTER 0

#define UNIFORM_WIDTH 40

#define SP_LOW 60
#define SP_HIGH 100

#define xstr(s) #s
#define str(s) xstr(s)
#define PATH str(/home/ye/Programs/Image Processing/NoiseModel/)

unsigned char * draw_cicle(int xdim, int ydim, double radius);
void writePGM(char* path, unsigned char *image, const int xdim, const int ydim);
unsigned char * uniform(unsigned char *image, int size, double width);
unsigned char * salt_and_pepper(unsigned char *image, int size, int low, int high);

int main(int argc, char *argv[]) {
    unsigned char *image = draw_cicle(XDIM, YDIM, RADIUS);

    srand((unsigned int)time(NULL));

    char path[80];
    strcpy(path, PATH);
    strcat(path, "circle.pgm");
    writePGM(path, image, XDIM, YDIM);

    unsigned char * uniImg = uniform(image, XDIM * YDIM, UNIFORM_WIDTH);

    strcpy(path, PATH);
    strcat(path, "uniform.pgm");
    writePGM(path, uniImg, XDIM, YDIM);

    unsigned char * saltyImg = salt_and_pepper(image, XDIM * YDIM, SP_LOW, SP_HIGH);

    strcpy(path, PATH);
    strcat(path, "salt-and-pepper.pgm");
    writePGM(path, saltyImg, XDIM, YDIM);

    free(image);
    free(uniImg);
    free(saltyImg);

    return 0;
}

unsigned char * uniform(unsigned char *image, int size, double width) {
    unsigned char *img = (unsigned char *)malloc(sizeof(unsigned char) * size);

    double val, u;
    int i;
    for(i = 0; i < size; i++) {
        u = rand () / (double)RAND_MAX;
        val = image[i] + width * (u - 0.5);

        if(val < 0)
            img[i] = 0;
        else if(val > 255)
            img[i] = 255;
        else
            img[i] = (unsigned char)val;
    }

    return img;
}

unsigned char * salt_and_pepper(unsigned char *image, int size, int low, int high) {
    unsigned char *img = (unsigned char *)malloc(sizeof(unsigned char) * size);

    int i, u;
    for(i = 0; i < size; i++) {
        u = rand() % (high - low + 1) + low;

        if(u == low)
            img[i] = 0;
        else if(u == high)
            img[i] = 255;
        else
            img[i] = image[i];
    }

    return img;
}

unsigned char * draw_cicle(int xdim, int ydim, double radius) {
    unsigned char * image = (unsigned char *)malloc(sizeof(unsigned char) * xdim * ydim);
    int centerX = xdim / 2, centerY = ydim / 2;
    double r;

    int i, j;
    for(i = 0; i < ydim; i++) {
        for(j = 0; j < xdim; j++) {
            r = sqrt(pow(j - centerX, 2) + pow(i - centerY, 2));
            if(r < radius)
                image[i * xdim + j] = INNER;
            else
                image[i * xdim + j] = OUTER;
        }
    }

    return image;
}

void writePGM(char* path, unsigned char *image, const int xdim, const int ydim) {
    FILE *fp = fopen(path, "w");
    if(fp) {
        fprintf(fp, "P5\n%d %d\n%d\n", xdim, ydim, 255);

        int i,j;
        for (j = 0; j < ydim; j++)
            for (i = 0; i < xdim; i++) {
                fputc(image[j * xdim + i], fp);
            }

        fclose(fp);
    } else {
        printf("Open file %s failed!\n", path);
        exit(1);
    }
}