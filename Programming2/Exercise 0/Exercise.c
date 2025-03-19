#include <stdio.h>
#include <stdlib.h>

void primeFactors(int a, int m){
    int *is_prime = (int *)malloc((a + 1) * sizeof(int));
    if (is_prime == NULL){
        printf("Error memory allocating");
        return;
    }
    for (int i = 0; i <= a; i++){
        is_prime[i] = 1;
    }
    is_prime[0] = 0;
    is_prime[1] = 0;
    for (int p = 2; p * p <= a; p++){
        if (is_prime[p] == 1){
            for (int i = p * p; i <= a; i += p){
                is_prime[i] = 0;
            }
        }
    }
    int b = 2;
    while ((m > 0) && (b <= a)){
        if ((is_prime[b] == 1) &&(a % b == 0)){
            m--;
            printf("%d\n", b);
        }
        b++;
    }
    free(is_prime);
}

int main() {
    int a, m;
    if (scanf("%d %d", &a, &m) != 2){
        printf("ERROR");
        return -1;
    } else if (a <= 1){
        printf("ERROR");
        return -1;
    }
    primeFactors(a, m);
    return 0;
}