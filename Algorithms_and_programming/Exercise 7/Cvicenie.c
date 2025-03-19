#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *sifruj(char *sprava, char *heslo) {
    int length = strlen(sprava);
    int length2 = strlen(heslo);
    int j = 0;
    
    char *result = (char *)malloc((length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL; 
    }

    for (int i = 0; i < length; i++) {
        if (j == length2) {
            j = 0;
        }
        result[i] = ((sprava[i] - 'A' + 1) + (heslo[j] - 'A' + 1))%26 + 'A' - 1;
        j++;
    }
    
    result[length] = '\0';
    return result;
}

char *odsifruj(char *sprava, char *heslo){
    int length = strlen(sprava);
    int length2 = strlen(heslo);
    int j = 0;
    
    char *result = (char *)malloc((length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL; 
    }
    for (int i = 0; i < length; i++) {
        if (j == length2) {
            j = 0;
        }
        result[i] = ((sprava[i] - 'A' + 1) - (heslo[j] - 'A' + 1) + 26)%26 + 'A' - 1;
        j++;
    }
    
    result[length] = '\0';
    return result;
}

int analyzuj(char *subor, int *riadky, int *medzery, int *cisla){
    FILE *file = fopen(subor, "r");
    if (file == NULL) {
        return -1;
    }
    int c;
    *riadky = 0;
    *medzery = 0;
    *cisla = 0;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            (*riadky)++;
        } else if (c == ' ') {
            (*medzery)++;
        } else if (c >= '0' && c <= '9') {
            (*cisla)++;
        }
        i++;
    }
    fclose(file);
    return i;
}

void cv1(){
    char sprava[100];
    char heslo[100];

    printf("Enter the message: ");
    scanf("%99s", sprava); 
    printf("Enter the password: ");
    scanf("%99s", heslo); 

    char *encrypted = sifruj(sprava, heslo);
    if (encrypted != NULL) {
        printf("Encrypted message: %s\n", encrypted);
        free(encrypted);
    } else {
        printf("Memory allocation failed.\n");
    }
}

void cv2(){
    char sprava[100];
    char heslo[100];

    printf("Enter the message: ");
    scanf("%99s", sprava); 
    printf("Enter the password: ");
    scanf("%99s", heslo); 

    char *encrypted = sifruj(sprava, heslo);
    if (encrypted != NULL) {
        printf("Encrypted message: %s\n", encrypted);
    } else {
        printf("Memory allocation failed.\n");
        return;
    }
    char *decrypted = odsifruj(encrypted, heslo);
    if (decrypted != NULL) {
        printf("Decrypted message: %s\n", decrypted);
        free(encrypted);
        free(decrypted);
    } else {
        printf("Memory allocation failed.\n");
    }
}

void cv3(){
    int riadky, medzery, cisla, velkost;
    velkost = analyzuj("vstup.txt", &riadky, &medzery, &cisla);
    if (velkost == -1){
        printf("Error while opening the file.\n");
        return;
    } else {
        printf("File size: %d\nPocet riadkov %d, medzery %d a cisla %d\n ", velkost, riadky, medzery, cisla);
    }
}

int main(){
    //cv1();
    //cv2();
    cv3();
    return 1;
}