#include <stdio.h>

int cv1() {
    FILE *f;
    f = fopen("floyd.txt", "w");
    int i,j, n, t;
    scanf("%d", &n);
    if (n < 1 || n > 10) {
        printf("Zadajte cele cislo z intervalu <1,10>\n");
        return 1;
    }
    t = 1;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            fprintf(f, "%d ", t);
            t++;
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int cv2() {
    FILE *f;
    f = fopen("rozmery.txt", "r");
    int r, s, i, j;
    if (fscanf(f, "%d %d", &r, &s) != 2) {
        printf("Nespravny format suboru\n");
        return 1;
    }
    for (i =1; i <=r; i++){
        printf("\n");
        for (j=1; j<=s; j++){
            printf("*");
        }
        s--;
    }
    fclose(f);
    return 0;
}

int cv3() {
    int n, i, j, m;
    scanf("%d", &n);
    m = n;
    if (n < 1 || n > 15) {
        printf("Zadajte cele cislo z intervalu <1,15>\n");
        return 1;
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            printf("%d ", j);
        }
        m--;
        printf("\n");
    }
    return 0;
}

int cv4(){
    FILE *f;
    f = fopen("cisla.txt", "w");
    int n, i, j, m;
    scanf("%d", &n);
    m = n;
    if (n < 1 || n > 15) {
        printf("Zadajte cele cislo z intervalu <1,15>\n");
        return 1;
    }
    for (i = 1; i <= n; i++) {
        for (j = m; j >= 1; j--) {
            fprintf(f, "%d ", j);
        }
        m--;
        fprintf(f, "\n");
    }
    return 0;
}

int cv5(){
    int n, k;
    scanf("%d", &n);
    for (k = 1; k <=n; k++){
        if (((k * (k + 1)) / 2) % 3 == 0){
            printf("%d ", k);
        }
    }
    return 0;
}

int cv6(){
    int n, i, j;
    scanf("%d", &n);
    if (n < 1 || n > 15 || n % 2 == 0) {
        printf("Zadajte cele cislo z intervalu <1,15> a neparne\n");
        return 1;
    }
    for (i = 1; i <= n + 1; i++){
        for (j =1; j <= i; j ++) {
            printf("*");
        }
        for (j = i; j <= n; j++){
            printf("-");
        }
        printf("\n");
    }
    for (i = n; i >= 1; i--){
        for (j =1; j <= i; j ++) {
            printf("*");
        }
        for (j = i; j <= n; j++){
            printf("-");
        }
        printf("\n");
    }
    return 0;
}

int cv7(){
    int n, i, j;
    scanf("%d", &n);
    if (n < 1 || n > 15 || n % 2 == 0) {
        printf("Zadajte cele cislo z intervalu <1,15> a neparne\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || i + j == n - 1 || i == n / 2 || j == n / 2) {
                printf("*");
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
    return 0;
}

int cv8(){
    int n, m, i, j, k;
    scanf("%d %d", &n, &m);
    if (n < 1 || n > 15 || n % 2 == 0) {
        printf("Zadajte cele cislo z intervalu <1,15> a neparne\n");
        return 1;
    }
    for (k=1; k <=m; k++){
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j || i + j == n - 1 || i == n / 2 || j == n / 2) {
                    printf("*");
                } else {
                    printf("-");
                }
            }
        printf("\n");
        }
    }
    return 0;
}

int cv9(){
    int n, m, i, j, k;
    scanf("%d %d", &n, &m);
    if (n < 1 || n > 15 || n % 2 == 0) {
        printf("Zadajte cele cislo z intervalu <1,15> a neparne\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        for (k = 1; k <= m; k++){
            for (int j = 0; j < n; j++) {
                if (i == j || i + j == n - 1 || i == n / 2 || j == n / 2) {
                    printf("*");
                } else {
                    printf("-");
                }
            }
        }
        printf("\n");
    }
    return 0;
}

int main(){
    //cv1();
    //cv2();
    //cv3();
    //cv4();
    //cv5();
    //cv6();
    //cv7();
    //cv8();
    //cv9();
    return 0; 
}