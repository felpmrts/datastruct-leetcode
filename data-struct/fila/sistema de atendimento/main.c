#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main() {
    Fila fila_normal = Inicializar();
    Fila fila_prioritaria = Inicializar();
    
    int opcao;
    int cont_normal = 1;
    int cont_prioritaria = 1;
    TipoDado cliente_atendido;

    do {
        printf("==============================\n");
        printf("Menu Principal:\n");
        printf("1. Gerar senha normal\n");
        printf("2. Gerar senha prioritaria\n");
        printf("3. Atender proximo cliente\n");
        printf("4. Mostrar filas\n");
        printf("0. Encerrar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");

        switch(opcao) {
            case 1:
                if (!FilaCheia(fila_normal)) {
                    Enfileirar(&fila_normal, cont_normal);
                    printf("Senha gerada: N%03d\n\n", cont_normal);
                    cont_normal++;
                } else {
                    printf("Fila normal cheia!\n\n");
                }
                break;
            case 2:
                if (!FilaCheia(fila_prioritaria)) {
                    Enfileirar(&fila_prioritaria, cont_prioritaria);
                    printf("Senha gerada: P%03d\n\n", cont_prioritaria);
                    cont_prioritaria++;
                } else {
                    printf("Fila prioritaria cheia!\n\n");
                }
                break;
            case 3:
                if (!FilaVazia(fila_prioritaria)) {
                    Desenfileirar(&fila_prioritaria, &cliente_atendido);
                    printf("Atendendo cliente prioritario: P%03d\n\n", cliente_atendido);
                } else if (!FilaVazia(fila_normal)) {
                    Desenfileirar(&fila_normal, &cliente_atendido);
                    printf("Atendendo cliente normal: N%03d\n\n", cliente_atendido);
                } else {
                    printf("Nenhum cliente na fila de espera.\n\n");
                }
                break;
            case 4:
                ImprimirFila(fila_prioritaria, 'P');
                ImprimirFila(fila_normal, 'N');
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n\n");
        }
    } while (opcao != 0);

    if (fila_normal.tab != NULL) free(fila_normal.tab);
    if (fila_prioritaria.tab != NULL) free(fila_prioritaria.tab);

    return 0;
}
