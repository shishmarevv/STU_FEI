#include <stdio.h>

void cv1() {
    FILE *file = fopen("vystup.txt", "w");
    if (file == NULL) {
        printf("Unable to open file");
        return;
    }

    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '.') {
            break;
        }
        if (65 <= ch && ch <= 90) {
            ch = ch + 32;
        } else if (97 <= ch && ch <= 122) {
            ch = '.';
        } else if (48 <= ch && ch <= 57) {
            ch = '-';
        } else if (ch == '\n') {
            // Leave newline characters unchanged
        } else {
            ch = '*';
        }

        fputc(ch, file);
    }

    fclose(file);
}

void cv2(){
    FILE *file = fopen("cisla.txt", "r");
    if (file == NULL) {
        printf("Unable to open file");
        return;
    }

    int ch;
    int array[100];
    int count = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (48 <= ch && ch <= 57) {
            int number = 0;
            do {
                number = number * 10 + (ch - '0');
                ch = fgetc(file);
            } while (48 <= ch && ch <= 57);

            if (number % 2 == 0) {
                array[count++]  = number;  
            }
        }
    }

    printf("Even numbers in reverse order:\n");
    for (int i = count - 1; i >= 0; i--) {
        printf("%d ", array[i]);
    }
    fclose(file);
}

void cv3(){
    float number;
    printf("Zadajte realne cislo: ");
    scanf("%f", &number);
    FILE *file = fopen("nasobky.txt", "w");
    if (file == NULL) {
        printf("Unable to open file");
        return;
    }
    int i;
    for (i = 1; i < 11; i++){
        fprintf(file, "%d:  %.2f, %.2f, %.2f \n", i, i*number, (i * number)*2, (i * number)*number);
    }

    fclose(file);
}

void cv4() {
    char inputChar;
    printf("Zadajte znak: ");
    inputChar = getchar();
    getchar(); // Consume newline character

    FILE *inputFile = fopen("znak.txt", "r");
    if (inputFile == NULL) {
        printf("Unable to open znak.txt\n");
        return;
    }

    FILE *outputFile = NULL;
    if (inputChar == 's') {
        outputFile = fopen("novy.txt", "w");
        if (outputFile == NULL) {
            printf("Unable to open novy.txt\n");
            fclose(inputFile);
            return;
        }
    }

    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        if (inputChar == 's') {
            fputc(ch, outputFile);
        } else {
            fputc(ch, stdout);
        }
    }

    fclose(inputFile);
    if (outputFile != NULL) {
        fclose(outputFile);
    }
}



int main() {
    //cv1();
    //cv2();
    //cv3();
    cv4();
    return 0;
}