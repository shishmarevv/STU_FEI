#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"
#include "data.h"


double weight(const int neuron, const int row, const int col){
    return weights[784 * neuron + 28 * row + col];
}

void weighted_sum(double *image, double *sums) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 784; j++) {
            sums[i] += image[j] * weight(i, j, 0);
        }
        sums[i] += bias[i];
    }
}

void space(const int width){
    for (int i = 1; i < width; i ++){
        putchar(' ');
    }
}

int main(void) {
    int mode;
    scanf("%d", &mode);
    if (mode == 1) {
        double *image = (double *)malloc(sizeof(double) * 784);
        if (image == NULL) {
            printf("Error allocating memory\n");
            return -1;
        }
        load_image(image, 784);
        print_image(image, 28, 28);
        free(image);
    } else if (mode == 2) {
        int neuron, row, col;
        scanf("%d", &neuron);
        scanf("%d", &row);
        scanf("%d", &col);
        printf("%lf", weight(neuron, row, col));
    } else if (mode == 3) {
        double *image = (double *)malloc(sizeof(double) * 784);
        if (image == NULL) {
            printf("Error allocating memory\n");
            return -1;
        }
        load_image(image, 784);
        double *sums = (double *)malloc(sizeof(double) * 10);
        if (sums == NULL) {
            free(image);
            printf("Error allocating memory\n");
            return -1;
        }
        weighted_sum(image, sums);
        for (int i = 0; i < 10; i++) {
            space(8);
            printf("%d", i);
            printf("%*.*f", 8, 2, sums[i]);
        }
        free(image);
        free(sums);
    }
    return 0;
}