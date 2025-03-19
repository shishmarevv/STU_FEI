#include <stdio.h>

void cv1(){
    printf("Hello world!\n");
}

void cv2(){
    int a, b, c, v, p;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    v = a*b*c;
    p = 2*a*b+2*b*c+2*c*a;
    printf("Volume %d\n",v);
    printf("Surface %d",p);
}

void cv3(){
    int a;
    float b, c, pi;
    pi = 3.14;
    scanf("%d", &a);
    b = 2*pi*a;
    c = pi*(a*a);
    printf("Obsah %f\n",c);
    printf("Obvod %f",b);
}

void cv4(){
    float a, b, c, v;
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);
    v = (a+b+c)/3;
    printf("Priemer %f\n",v);
}

void cv5(){
    float a;
    scanf("%f", &a);
    a = 1.2*a;
    printf("S danou %f",a);
}

void cv6(){
    float a, b, c;
    scanf("%f", &a);
    scanf("%f", &b);
    a = a/100;
    c = b/(a*a);
    printf("BIM %f",c);
}

int main(){
    //cv1();
    //cv2();
    //cv3();
    //cv4();
    //cv5();
    //cv6();
    return 0;
}