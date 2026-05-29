#include <stdio.h>

// Sem a condção de parada caso o vetor esteja ordenado

void bubble_sort(int *T, int n) {

    int i, k, temp;

    for(k = n - 1; k >= 1; k--) {
        for(i = 1; i <= k; i++) {
            if(T[i] < T[i-1]) {
                temp = T[i];
                T[i]= T[i-1];
                T[i-1] = temp;
            }
        }
    }

}

// Com a condição de parada

/*
void bubble_sort_otimizado(int *T, int n) {
    int i, k, temp;
    int trocou; // Esta é a nossa condição de parada (flag)

    for(k = n - 1; k >= 1; k--) {
        trocou = 0; // No início de cada rodada, assumimos que o vetor está ordenado

        for(i = 1; i <= k; i++) {
            if(T[i] < T[i-1]) {
                // Se entrou aqui, significa que o vetor NÃO estava ordenado
                temp = T[i];
                T[i] = T[i-1];
                T[i-1] = temp;
                
                trocou = 1; // Ativa o sinal de que houve modificação
            }
        }

        // CONDIÇÃO DE PARADA: Se terminou o laço interno e 'trocou' continua 0,
        // significa que nenhuma troca foi feita. O vetor já está pronto.
        if(trocou == 0) {
            break; // Interrompe o laço externo imediatamente
        }
    }
}
*/

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

    bubble_sort(T, n);

    printf("\nVetor depois: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", T[i]);
    }

    printf("\n");

    return 0;
}