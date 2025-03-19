#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

double stepf(double x){
    if (x >= 0.0){
        return 1.0;
    } else {
        return 0.0;
    }
}

double ReLu(double x){
    if (x >= 0.0){
        return x;
    } else {
        return 0.0;
    }
}

double squareplus(double x) {
    return (0.5 * (x + sqrt(x*x + 2.0)));
}

double gauss(double x) {
    return exp(-(x*x));
}

double htan(double x){
    return ((exp(x) - exp(-x))/(exp(x) + exp(-x)));
}

double swish(double x){
    return ((x)/(1.0 + exp(-(0.5 * x))));
}

void space(int width){
    for (int i = 0; i < width - 1; i ++){
        putchar(' ');
    }
}

void automode(double start, double stop, double step, int precision, int width){
    space(width);
    printf("x");
    space(width);
    printf("1");
    space(width);
    printf("2");
    space(width);
    printf("3");
    space(width);
    printf("4");
    space(width);
    printf("5");
    space(width);
    printf("6");
    printf("\n");
    for (double i = start; i <= stop; i = i + step){
        printf("%*.*f", width, precision, i);
        printf("%*.*f", width, precision, stepf(i));
        printf("%*.*f", width, precision, ReLu(i));
        printf("%*.*f", width, precision, squareplus(i));
        printf("%*.*f", width, precision, gauss(i));
        printf("%*.*f", width, precision, htan(i));
        printf("%*.*f", width, precision, swish(i));
        printf("\n");
    }
}

void funcprint(double (*func)(double), double start, double stop, double step, int precision, int width){
    for(double i = start; i <= stop; i = i + step){
        printf("%*.*f", width, precision, func(i));
    }
    printf("\n");
}

void manualmode (double start, double stop, double step, int precision, int width, int *input, int len){
    space(width);
    printf("x");
    for (double i = start; i <= stop; i = i + step){
        printf("%*.*f", width, precision, i);
    }
    printf("\n");
    for (int i = 0; i < len; i++){
        if (input[i] == 1){
            space(width);
            printf("%d", input[i]);
            funcprint(stepf, start, stop, step, precision, width);
        } else if (input[i] == 2){
            space(width);
            printf("%d", input[i]);
            funcprint(ReLu, start, stop, step, precision, width);
        } else if (input[i] == 3){
            space(width);
            printf("%d", input[i]);
            funcprint(squareplus, start, stop, step, precision, width);
        } else if (input[i] == 4){
            space(width);
            printf("%d", input[i]);
            funcprint(gauss, start, stop, step, precision, width);
        } else if (input[i] == 5){
            space(width);
            printf("%d", input[i]);
            funcprint(htan, start, stop, step, precision, width);
        } else if (input[i] == 6){
            space(width);
            printf("%d", input[i]);
            funcprint(swish, start, stop, step, precision, width);
        }
    }
}

int main(){
    double start, stop, step;
    int precision, width;
    unsigned int capacity = 10, size = 0;
    int *input = (int *)malloc(capacity * sizeof(int));
    if (input == NULL){
        printf("ERROR allocating memory");
        return 0;
    }

    //FIXME: Исправить обработку ввода, когда не введены основыне переменные
    if (scanf("%lf %lf %lf %d %d", &start, &stop, &step, &precision, &width) != 5) {
        printf("E1\n");
        free(input);
        return 0;
    }
    if (start >= stop){
        printf("E2\n");
        free(input);
        return 0;
    }
    int c, t = 0;
    while (scanf("%d", &c) == 1) {
        if (t == 0) t = 1;
        if ((1 <= c) && (c <= 6 )) t = 2;
        if (size >= capacity - 1) {
            capacity *= 2;
            int *temp = (int *)realloc(input, capacity * sizeof(int));
            if (temp == NULL) {
                free(input);
                printf("Error reallocating memory\n");
                return 0;
            }
            input = temp;
        }
        input[size++] = c;
    }
    if (t == 0){
        automode(start, stop, step, precision, width);
    } else if (t == 2) {
        manualmode(start, stop, step, precision, width, input, size);
    }
    free(input);
    return 0;
}