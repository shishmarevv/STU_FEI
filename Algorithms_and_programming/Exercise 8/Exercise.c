#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMatrix(int matrix[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) { 
            printf("%d    ", matrix[i][j]); 
        }
        printf("\n");
    }
}

int NacitajMaticu(char *subor, int matica[10][10]){
    FILE *file;
    file = fopen(subor, "r");
    if (file == NULL){
        printf("Subor sa nepodarilo otvorit\n");
        return 0;
    }
    int i = 0, j = 0, res = 0;
    while (fscanf(file, "%d", &matica[i][j]) != EOF) {
        j++;
        if (j == 10) {
            j = 0;
            i++;
            if (i == 10) {
                res = 1;
                break;
            }
        }
    }
    //printMatrix(matica);
    return res;
    fclose(file);
}

int  AnalyzujMaticu(int matica [10][10], int *zaporne,int *neparne){
    int zap = 0, nep = 0, max = matica[0][0];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) { 
            if (matica[i][j] < 0) {
                zap++;
            }
            if (matica[i][j] % 2 != 0) {
                nep++;
            }
            if (matica[i][j] > max) {
                max = matica[i][j];
            }
        }
    }
    *zaporne = zap;
    *neparne = nep;
    return max;
}


int main(){
    int matrix[10][10], result;
    result = NacitajMaticu("matica.txt", matrix);
    if (result == 0){
        printf("Nacitanie matice zlyhalo\n");
        return 0;
    } else {
        printf("Matica bola nacitana\n");
        int zaporne, neparne, max;
        NacitajMaticu("matica.txt", matrix);
        max = AnalyzujMaticu(matrix, &zaporne, &neparne);
        printf("Zapornych cisel: %d\n", zaporne);
        printf("Neparnych cisel: %d\n", neparne);
        printf("Najvacsie cislo: %d\n", max);
        printMatrix(matrix);
    }
    return 0;
}