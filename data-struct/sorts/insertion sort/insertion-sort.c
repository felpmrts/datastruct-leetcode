#include <stdio.h>

void insertion_sort(int *T, int n) {

    int k, i, v;

    for(k = 1; k <= n - 1; k++) {
        v = T[k];
        i = k - 1;

        while(i >= 0 && v < T[i]) {
            T[i+1] = T[i];
            i = i-1;
        } 

        T[i+1] = v;
    }
}

int main() {

    int T[10];
    int n = 10;

    printf("Digite 10 numeros para o vetor:\n");
    for(int i = 0; i < n; i++){
        printf("T[%d]: ", i);
        scanf(" %d", &T[i]);
    }

    printf("Vetor antes: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }

    insertion_sort(T, n);

    printf("\nVetor depois: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }

    printf("\n");

    return 0;
}