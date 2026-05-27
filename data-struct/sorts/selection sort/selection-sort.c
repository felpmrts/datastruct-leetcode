#include <stdio.h>

void selection_sort(int *T, int n) {

    int k, i, imax, temp;

    for(k = n - 1; k >= 1; k--) {

        imax = 0;

        for(i = 1; i <= k; i++) {
            if(T[imax] < T[i]) {
                imax = i;
            }
        }

        temp =  T[k];
        T[k] = T[imax];
        T[imax] = temp; 
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

    selection_sort(T, n);

    printf("\nVetor depois: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }

    printf("\n");

    return 0;
}