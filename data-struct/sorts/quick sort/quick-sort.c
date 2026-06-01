#include <stdio.h>

int particionamento(int *T, int imin, int imax) {
    int v, i, j, temp;
    
    v = T[imax]; 
    i = imin;
    j = imax - 1;

    while (i <= j) {
        
        while (i < imax && T[i] <= v) {
            i++;
        }
        
        while (j >= imin && T[j] >= v) {
            j--;
        }
        
        if (i < j) {
            temp = T[i];
            T[i] = T[j];
            T[j] = temp;
        }
    }
    
    T[imax] = T[i];
    T[i] = v;

    return i; 
}

void classifRapid(int *T, int imin, int imax) {
    int i;
    if (imin < imax) { 
        i = particionamento(T, imin, imax); 
        classifRapid(T, imin, i - 1);       
        classifRapid(T, i + 1, imax);       
    }
}

void quick_sort(int *T, int n) {
    classifRapid(T, 0, n - 1); 
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

    quick_sort(T, n);

    printf("\nVetor depois: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }

    printf("\n");

    return 0;
}