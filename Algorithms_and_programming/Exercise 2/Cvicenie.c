#include <stdio.h>

void cv1(){
    int x, y, z;
    printf("zadaj dve cisla oddelene medzerou: ");
    scanf("%d %d", &x, &y);
    z = (x>=y) ? x : y;
    printf("a) vacsie z cisel: %d \n", z);
    if (y > x)
    {
        printf("b) mensie z cisel : %d \n", x);
    }
}

void cv2(){
    int a;
    printf("zadaj 1 znak: ");
    a = getchar();
    if ((57 >= a) && ( a >= 48)){
        printf("To je cislo");
    } else {
        if ((90 >= a) && ( a >= 65)) {
            printf("To je velka bukva");
        } else {
            if ((122 >= a) && ( a >= 97)){
                printf("To je mala bukva");
            } else {
                printf("To je ina znacka");
            }
        }
    }
}

int dec2bin(int num)
{
    int bin = 0, k = 1;

    while (num)
    {
        bin += (num % 2) * k;
        k *= 10;
        num /= 2;
    }

    return bin;
}

int dec2hex(int num)
{
    int hex = 0, k = 1;

    while (num)
    {
        hex += (num % 16) * k;
        k *= 10;
        num /= 2;
    }

    return hex;
}

void cv3(){
    int a;
    char b;
    printf("zadaj 1 znak: ");
    a = getchar();
    printf("V decimalnej: %d \n", a);
    printf("V binarnej: %d \n", dec2bin(a));
    printf("V hexidecimalnej: %d \n", dec2hex(a));
    if ((122 >= a) && ( a >= 97)){
        a = a - 32;
        printf("Vacsia bukva: ");
        putchar(a);
        printf("\nV decimalnej: %d \n", a);
        printf("V binarnej: %d \n", dec2bin(a));
        printf("V hexidecimalnej: %d \n", dec2hex(a));
    }
}

int main(){
    //cv1();
    //cv2();
    //cv3();
    return 0;
}