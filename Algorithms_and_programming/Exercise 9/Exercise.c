#include <stdio.h>
#include <stdlib.h>

int **create(int rows, int cols) {
    int **p = (int **)malloc(rows * sizeof(int *));
    if (p == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        p[i] = (int *)malloc(cols * sizeof(int));
        if (p[i] == NULL) {
            for (int j = 0; j < i; j++) free(p[j]);
            free(p);
            return NULL;
        }
    }
    return p;
}

int **AlokujNapln(int *rows, int *cols) {
    FILE *file = fopen("vstup.txt", "r");
    if (file == NULL) {
        printf("Can't open file\n");
        return NULL;
    }

    if (fscanf(file, "%d %d", rows, cols) != 2) {
        printf("Error in sizes reading\n");
        fclose(file);
        return NULL;
    }
    printf("Matrix sizes %d x %d\n", *rows, *cols);

    int **matrix = create(*rows, *cols);
    if (matrix == NULL) {
        printf("Error in memory allocation\n");
        fclose(file);
        return NULL;
    }

    printf("Reading Matrix\n");
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("Error in reading element [%d][%d].\n", i, j);
                fclose(file);
                for (int k = 0; k <= i; k++) free(matrix[k]);
                free(matrix);
                return NULL;
            }
        }
    }

    fclose(file);
    printf("Matrix successfully created\n");
    return matrix;
}

int main() {
    int rows, cols;
    int **matrix = AlokujNapln(&rows, &cols);

    if (matrix == NULL) {
        printf("Matrix wasn't created\n");
        return 1;
    }

    printf("Matrix\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
