#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <string.h>

#pragma comment(lib, "winmm.lib")

//Blok 1

void exercise1_1() {
    int input1 = 0, input2 = 0;
    printf("Input: ");
    scanf("%d %d", &input1, &input2);
    __asm__ (
        "mov %1, %%eax\n\t"
        "mov %2, %%ebx\n\t"
        "add %%ebx, %%eax\n\t"
        "mov %%eax, %0\n\t"
        : "=r" (input1)
        : "r" (input1), "r" (input2)
        : "%eax", "%ebx"
    );
    printf("Output: %d\n", input1);
}

void exercise1_3() {
    int input = 0,output = 0;
    printf("Input: ");
    scanf("%d", &input);
    __asm__ (
        "mov %1, %%eax\n\t"
        "cmp $10, %%eax\n\t"
        "jg first\n\t"
        "add $48, %%eax\n\t"
        "jmp second\n\t"
        "first:\n\t"
        "add $55, %%eax\n\t"
        "second:\n\t"
        "mov %%eax, %0\n\t"
        : "=r" (output)
        : "r" (input)
        : "%eax"
    );
    printf("Output: %c\n", (char) output);
}

void exercise1_4() {
    char out1[5] = {0}, out2[5] = {0}, out3[5] = {0};
    __asm__ (
        "mov $0, %%eax\n\t"
        "cpuid\n\t"
        "mov %%ebx, %0\n\t"
        "mov %%edx, %1\n\t"
        "mov %%ecx, %2\n\t"
        : "=m" (out1),
        "=m" (out2),
        "=m" (out3)
        :
        : "eax", "ebx", "ecx", "edx", "memory"
    );
    printf("Output: %s%s%s\n", out1, out2, out3);
}

//Blok 2

void exercise2() {
    char str[22] = "Computer_architecture\0";
    printf("String: %s\n", str);
    char *ptr = str;
    printf("Pointer: %p\n", ptr);
    ptr++;
    *ptr = '7';
    printf("Modified String: %s\n", str);
    //ptr = ptr + 1000000000;
    //*ptr = '7';
    int num[5] = {1, 2, 3, 4, 5};
    printf("Array: ");
    int u = 0;
    for (int i = 0; i < 5; i++) {
        u++;
        printf("%d ", num[i]);
    }
    printf("\n");
    int *ptr2 = num;
    printf("Pointer: %p\n", ptr2);
    ptr2++;
    *ptr2 = 77;
    printf("Modified Array: ");
    for (int i = 0; i < 5; i++) printf("%d ", num[i]);
    printf("\n");
}

void color(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void cursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void menu_graphics() {
    system("cls");

    color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("  _______ _        _______           _______         \n");

    color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf(" |__   __(_)      |__   __|         |__   __|        \n");
    printf("                  MULTIMEDIA                         \n");
    printf(" |__   __(_)      |__   __|         |__   __|        \n");

    color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("  _______ _        _______           _______         \n");

    color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("- 1. Enter file name                        -\n");
    printf("- 2. Play                                   -\n");
    printf("- 3. Pause                                  -\n");
    printf("- 4. Close                                  -\n");
    printf("- 0. Exit                                   -\n");

    color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("  _______ _        _______           _______         \n");
    color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\nInput: ");
}

//Blok 4
void exercise4() {
    int input = -1;

    while (input != 0) {
        menu_graphics();
        scanf("%d", &input);
        while (getchar() != '\n');
        char file[256];

        switch (input) {
            case 1:
                printf("Enter Filename: ");
                fgets(file, sizeof(file), stdin);
                file[strcspn(file, "\n")] = '\0';
                char command[256];
                sprintf(command, "open \"%s\" alias main", file);
                if (mciSendString(command, NULL, 0, NULL) != 0) {
                    printf("Error opening file\n");
                }
                break;
            case 2:
                if (mciSendString("play main", NULL, 0, NULL) != 0) {
                    printf("Error playing file\n");
                }
                break;
            case 3:
                if (mciSendString("pause main", NULL, 0, NULL) != 0) {
                    printf("Error pausing file\n");
                }
                break;
            case 4:
                if (mciSendString("close main", NULL, 0, NULL) != 0) {
                    printf("Error stopping file\n");
                }
            case 0:
                break;
            default:
                printf("Invalid Choice\n");
                break;
        }
    }
    mciSendString("close all", NULL, 0, NULL);
}

//Blok 5

void exercise5_2() {
    //SetConsoleOutputCP(65001);
    char *name = "Viktor Shishmarev";
    char *age = "19";
    char *height = "182 cm";
    char *weight = "70 kg";
    int x = 15, y = 10;
    char vertical = (char ) 186;
    char horizontal = (char) 205;
    char cornertl = 201;
    char cornertr = 187;
    char cornerbl = 200;
    char cornerbr = 188;
    int border = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int text = FOREGROUND_RED | FOREGROUND_INTENSITY;
    unsigned int maxLen = strlen(name);
    if (strlen(age) > maxLen) maxLen = strlen(age);
    if (strlen(height) > maxLen) maxLen = strlen(height);
    if (strlen(weight) > maxLen) maxLen = strlen(weight);
    color(border);
    cursor(x, y);
    printf("%c", cornertl);
    for (int i = 0; i < maxLen + 2; i++) printf("%c", horizontal);
    printf("%c", cornertr);
    color(text);
    cursor(x, y + 1);
    printf("%c %-*s %c", vertical, maxLen, name, vertical);
    cursor(x, y + 2);
    printf("%c %-*s %c", vertical, maxLen, age, vertical);
    cursor(x, y + 3);
    printf("%c %-*s %c", vertical, maxLen, height, vertical);
    cursor(x, y + 4);
    printf("%c %-*s %c", vertical, maxLen, weight, vertical);
    color(border);
    cursor(x, y + 5);
    printf("%c", cornerbl);
    for (int i = 0; i < maxLen + 2; i++) printf("%c", horizontal);
    printf("%c", cornerbr);
    color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main(void) {
    printf("Input exercise number: ");
    int blok, exercise;
    scanf("%d.%d", &blok, &exercise);
    switch (blok) {
        case 1:
            switch (exercise) {
                case 1:
                    exercise1_1();
                    break;
                case 3:
                    exercise1_3();
                    break;
                case 4:
                    exercise1_4();
                    break;
                default:
                    printf("Exercise not found\n");
                    break;
            }
            break;
        case 2:
            exercise2();
            break;
        case 4:
            exercise4();
            break;
        case 5:
            switch (exercise) {
                case 2:
                    exercise5_2();
                    break;
                default:
                    printf("Exercise not found\n");
                    break;
            }
            break;
        default:
            printf("Block not found\n");
            break;
    }
    return 0;
}