#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Exercise 6
int HEXtoDEC(char *hex){
    int dec = 0, base = 1;
    for (int i = (int) strlen(hex) - 2; i >= 0; i--){
        if (('0' <= hex[i]) && (hex[i] <= '9')){
            dec += base*(hex[i] - '0');
        } else if (('A' <= hex[i]) && (hex[i] <= 'F')) {
            dec += base*(hex[i] - 'A' + 10);
        } else {
            printf("ERROR\n");
            return -1;
        }
        base *= 16;
    }
    return dec;
}

char* DECtoHEX(int dec) {
    char* hex = (char*)malloc((dec/16 + 2) * sizeof(char));
    if (hex == NULL) {
        printf("error memory allocation");
        return "0\0";
    }
    char* hex_t = (char*)malloc((dec/16 + 2) * sizeof(char));
    if (hex_t == NULL) {
        printf("error memory allocation");
        free(hex);
        return "0\0";
    }
    int index = 0;

    if (dec == 0) {
        hex[0] = '0';
        hex[1] = '\0';
        return hex;
    }

    while (dec > 0) {
        const int temp = dec % 16;
        hex_t[index++] = (temp < 10) ? (temp + '0') : (temp - 10 + 'A');
        dec /= 16;
    }
    index--;
    for (int i = 0; i <= index; i ++){
        hex[i] = hex_t[index - i];
    }
    index++;
    hex[index] = '\0';
    return hex;
}

int exercise6(){
    unsigned int capacity = 10, size = 0;
    char *input = (char *)malloc(capacity * sizeof(char));
    if (input == NULL) {
        printf("Error allocating memory\n");
        return -1;
    }
    printf("Enter the hex string: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (size >= capacity - 1) {
            capacity *= 2;
            char *temp = (char *)realloc(input, capacity * sizeof(char));
            if (temp == NULL) {
                free(input);
                printf("Error reallocating memory\n");
                return -1;
            }
            input = temp;
        }
        input[size++] = (char)c;
    }
    input[size] = '\0';
    int n = size;
    int sum = 0;
    char *cursor = (char *)malloc(3*sizeof(char));
    for (int i = 1; i < n - 2; i = i + 2){
        cursor[0] = input[i];
        cursor[1] = input[i + 1];
        sum += HEXtoDEC(cursor);
    }
    free(cursor);
    sum = sum%256;
    sum = 255 - sum + 1;
    char *result = DECtoHEX(sum);
    input[n - 2] = result[0];
    input[n - 1] = result[1];
    printf("%s\n", input);
    free(result);
    free(input);
    return 0;
}

//Exercise 5
int factorial(const int n){
    if (n == 0){
        return 1;
    } else {
        return n*factorial(n-1);
    }
}

float absolute_value(const float arg){
    if (arg >= 0.0){
        return arg;
    } else {
        return (float)-1.0 * arg;
    }
}

float power(const float x, const int n){
    float result = (float)1.0;
    for (int i = 0; i < n; i++){
        result*= x;
    }
    return result;
}

float Mysin(const float arg, const float eps){
    int checker = 0, counter = 0;
    float result = (float) 0.0, oldresult = (float) 0.0;
    while (checker < 2){
        oldresult = result;
        result = result + ((power((float)-1.0, counter) * power(arg, 2*counter + 1))/((float)factorial(2*counter + 1)));
        if (absolute_value(result - oldresult) <= eps) checker ++;
        counter++;
    }
    return result;
}

float Mycos(const float arg, const float eps){
    int checker = 0, counter = 0;
    float result = (float) 0.0, oldresult = (float) 0.0;
    while (checker < 2){
        oldresult = result;
        result = result + ((power((float) -1.0, counter) * power(arg, 2*counter))/((float)factorial(2*counter)));
        if (absolute_value(result - oldresult) <= eps) checker ++;
        counter++;
    }
    return result;
}

int exercise5(){
    float arg, eps;
    printf("Enter argument and epsilon: ");
    if(scanf("%f %f", &arg, &eps) != 2){
        printf("Error reading");
        return -1;
    }
    float sinus = Mysin(arg, eps), cosinus = Mycos(arg, eps);
    float sin_org =  sinf(arg), cos_org = cosf(arg);
    printf("Results:\n SIN: %f \n COS: %f\n", sinus, cosinus);
    printf("Difference:\n SIN: %f \n COS: %f\n", absolute_value(sinus - sin_org), absolute_value(cosinus - cos_org));
    return 1;
}

//Exercise 3
int count_ones(int n) {
    int counter = 0;
    while (n) {
        counter += n & 1;
        n = n >> 1;
    }
    return counter;
}
int exercise3() {
    int input;
    printf("Enter number: ");
    scanf("%d", &input);
    printf("%d\n", count_ones(input));
    return 0;
}

//uvod

void mojaFunkica1() {
    for (int i = 1; i < 101; i++) {printf("%d\n", i);}
}

void mojaFunkica2() {
    for (int i = 0; i <= 30; i++) {
        if (i % 2 == 0) printf("%d\n", i);
    }
}

void mojaFunkica3() {
    for (int i = 0; i <= 30; i++) {
        if (i % 2 == 1) printf("%d\n", i);
    }
}

int uvod() {
    mojaFunkica1();
    mojaFunkica2();
    mojaFunkica3();
    return 0;
}

int main() {
    exercise6();
    exercise5();
    exercise3();
    uvod();
    return 0;
}