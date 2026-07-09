#include <stdio.h>
#include <stdlib.h>

typedef float TipoDado;

/* Estrutura de cada nó (célula) da lista */
typedef struct Cell {
    TipoDado dado;
    struct Cell *seguinte;
} TipoCelula;

/* Estrutura de controle da fila */
typedef struct {
    TipoCelula *cabeca;
    TipoCelula *queue;
} FilaEncadeada;

/* --- Primitivas da Fila com Lista Encadeada --- */

FilaEncadeada InicializarF() {
    FilaEncadeada filavazia;
    filavazia.cabeca = NULL;
    filavazia.queue = NULL;
    return filavazia;
}

int FilaVazia(FilaEncadeada F) {
    return (F.cabeca == NULL) ? 1 : 0;
}

void InserirF(FilaEncadeada *pF, TipoDado elem) {
    TipoCelula *q;
    q = (TipoCelula*) malloc(sizeof(TipoCelula));
    q->dado = elem;
    q->seguinte = NULL;
    
    if (pF->cabeca == NULL) {
        pF->cabeca = q;
        pF->queue = q;
    } else {
        pF->queue->seguinte = q;
        pF->queue = q;
    }
}

char RemoverF(FilaEncadeada *pF, TipoDado *pelem) {
    TipoCelula *p;
    if (pF->cabeca == NULL)
        return 1;
        
    *pelem = pF->cabeca->dado;
    p = pF->cabeca;
    pF->cabeca = pF->cabeca->seguinte;
    
    if (pF->cabeca == NULL) {
        pF->queue = NULL;
    }
    
    free(p);
    return 0;
}

void DestruirF(FilaEncadeada *pF) {
    TipoCelula *p, *q;
    p = pF->cabeca;
    while (p != NULL) {
        q = p;
        p = p->seguinte;
        free(q);
    }
    pF->cabeca = NULL;
    pF->queue = NULL;
}

/* --- Função Principal (Main) --- */

int main() {
    /* Cria a fila com os ponteiros apontando para NULL */
    FilaEncadeada minhaFila = InicializarF();
    TipoDado valorRemovido;

    printf("=== Testando Fila Dinamica (Lista Encadeada) ===\n\n");

    /* 1. Verifica se a fila começou vazia */
    if (FilaVazia(minhaFila)) {
        printf("Sucesso: A fila iniciou vazia.\n\n");
    }

    /* 2. Inserindo elementos dinamicamente */
    /* Diferente do vetor, aqui poderiamos inserir quantos elementos a memória RAM aguentar */
    printf("Enfileirando elementos: 10.5, 20.0, 30.5, 40.0, 50.0...\n");
    InserirF(&minhaFila, 10.5);
    InserirF(&minhaFila, 20.0);
    InserirF(&minhaFila, 30.5);
    InserirF(&minhaFila, 40.0);
    InserirF(&minhaFila, 50.0);

    /* 3. Mostrando o estado atual dos ponteiros de controle */
    printf("Fila criada com sucesso!\n");
    printf("Endereco do primeiro (cabeca): %p (Valor: %.1f)\n", (void*)minhaFila.cabeca, minhaFila.cabeca->dado);
    printf("Endereco do ultimo (queue): %p (Valor: %.1f)\n\n", (void*)minhaFila.queue, minhaFila.queue->dado);

    /* 4. Removendo os dois primeiros elementos (FIFO: 10.5 e 20.0 devem sair) */
    printf("Removendo 2 elementos da frente da fila...\n");
    if (RemoverF(&minhaFila, &valorRemovido) == 0) {
        printf("Removido com sucesso: %.1f\n", valorRemovido);
    }
    if (RemoverF(&minhaFila, &valorRemovido) == 0) {
        printf("Removido com sucesso: %.1f\n", valorRemovido);
    }

    /* 5. Veja como a cabeça mudou, mas a cauda (queue) continua apontando para o mesmo nó (50.0) */
    printf("\nEstado dos ponteiros apos as remocoes:\n");
    printf("Nova cabeca atual da fila: %.1f\n", minhaFila.cabeca->dado);
    printf("O ultimo da fila continua sendo: %.1f\n\n", minhaFila.queue->dado);

    /* 6. Esvaziando o restante da fila usando um laço */
    printf("Descarregando o restante da fila ate ficar vazia:\n");
    while (!FilaVazia(minhaFila)) {
        RemoverF(&minhaFila, &valorRemovido);
        printf("Removido: %.1f\n", valorRemovido);
    }

    /* 7. Faz a limpeza final de segurança */
    DestruirF(&minhaFila);
    printf("\nFila totalmente destruida e memoria desalocada com sucesso.\n");

    return 0;
}