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
        sums[i] = 0.0;
        for (int j = 0; j < 784; j++) {
            sums[i] += image[j] * weight(i, 0, j);
        }
        sums[i] += bias[i];
        if (sums[i]*100 - trunc(sums[i]*100) == 0.5) {
            sums[i] = floor(sums[i]*100) / 100;
        }
    }
}

void space(const int width){
    for (int i = 1; i < width; i ++){
        putchar(' ');
    }
}

double max(double *array) {
    double max = array[0];
    for (int i = 1; i < 10; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

void softmax(double *z) {
    double max_val = z[0];
    for (int i = 1; i < 10; i++) {
        if (z[i] > max_val) {
            max_val = z[i];
        }
    }
    double sum_exp = 0.0;
    for (int i = 0; i < 10; i++) {
        z[i] = exp(z[i] - max_val);
        sum_exp += z[i];
    }
    for (int i = 0; i < 10; i++) {
        z[i] /= sum_exp;
    }
}

int findmax(double *array) {
    double max = array[0];
    int index = 0;
    for (int i = 1; i < 10; i++) {
        if (array[i] > max) {
            max = array[i];
            index = i;
        }
    }
    return index;
}

void swish_act(double *sums) {
    for (int i = 0; i < 10; i++) {
        sums[i] = swish(sums[i]);
    }
}

int main(void) {
    unsigned int mode;
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
        printf("%.2lf", weight(neuron, row, col));
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
            printf("%8.2lf\n",  sums[i]);
        }
        free(image);
        free(sums);
    } else if (mode == 4) {
        double *sums = (double *)malloc(sizeof(double) * 10);
        if (sums == NULL) {
            printf("Error allocating memory\n");
            return -1;
        }
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &sums[0], &sums[1], &sums[2], &sums[3], &sums[4], &sums[5], &sums[6], &sums[7], &sums[8], &sums[9]);
        softmax(sums);
        for (int i = 0; i < 10; i++) {
            printf("%.2lf ", sums[i]);
        }
        free(sums);
    } else if (mode == 5) {
        double *sums = (double *)malloc(sizeof(double) * 10);
        if (sums == NULL) {
            printf("Error allocating memory\n");
            return -1;
        }
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &sums[0], &sums[1], &sums[2], &sums[3], &sums[4], &sums[5], &sums[6], &sums[7], &sums[8], &sums[9]);
        printf("%d", findmax(sums));
        free(sums);
    } else if (mode == 6) {
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
        swish_act(sums);
        softmax(sums);
        printf("%d", findmax(sums));
        free(image);
        free(sums);
    } else if (mode == 7) {
        int count;
        double chances = (double) 0;
        scanf("%d", &count);
        int *values = (int *)malloc(sizeof(int) * count);
        if (values == NULL) {
            printf("Error allocating memory\n");
            return -1;
        }
        int *neuro_values = (int *)malloc(sizeof(int) * count);
        if (neuro_values == NULL) {
            printf("Error allocating memory\n");
            free(values);
            return -1;
        }
        for (int i = 0; i < count; i++) {
            scanf("%d", &values[i]);
        }
        double *image = (double *)malloc(sizeof(double) * 784);
        if (image == NULL) {
            printf("Error allocating memory\n");
            free(values);
            free(neuro_values);
            return -1;
        }
        double *sums = (double *)malloc(sizeof(double) * 10);
        if (sums == NULL) {
            free(image);
            free(values);
            free(neuro_values);
            printf("Error allocating memory\n");
            return -1;
        }
        for (int i = 0; i < count; i++) {
            load_image(image, 784);
            weighted_sum(image, sums);
            swish_act(sums);
            softmax(sums);
            int res = findmax(sums);
            neuro_values[i] = res;
            if (res == values[i]) {
                chances++;
            }
        }
        chances = (chances / count)*100.00;
        printf("%.2lf ", chances);
        for (int i = 0; i < count; i++) {
            printf("%d-%d-%d ", i, values[i], neuro_values[i]);
        }
        free(image);
        free(sums);
        free(values);
        free(neuro_values);
    }
    return 0;
}