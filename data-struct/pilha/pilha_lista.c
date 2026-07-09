#include <stdio.h>
#include <stdlib.h>

typedef float TipoDado;

typedef struct Cell {
    TipoDado dado;
    struct Cell *seguinte;
} TipoCelula;

typedef TipoCelula* Pilha;

Pilha InicializarP() {
    return NULL;
}

int PilhaVazia(Pilha P) {
    return (P == NULL) ? 1 : 0;
}

int PilhaCheia(Pilha P) {
    return 0;
}

int AcessarTopoP(Pilha P, TipoDado *pelem) {
    if (PilhaVazia(P)) {
        return 1;
    }
    *pelem = P->dado;
    return 0;
}

int Empilhar(Pilha *pP, TipoDado elem) {
    TipoCelula *nova;
    nova = (TipoCelula*) malloc(sizeof(TipoCelula));
    if (nova == NULL) {
        return 1;
    }
    nova->dado = elem;
    nova->seguinte = *pP;
    *pP = nova;
    return 0;
}

int Desempilhar(Pilha *pP, TipoDado *pelem) {
    TipoCelula *aux;
    if (PilhaVazia(*pP)) {
        return 1;
    }
    aux = *pP;
    *pelem = aux->dado;
    *pP = aux->seguinte;
    free(aux);
    return 0;
}

void EsvaziarP(Pilha *pP) {
    TipoDado aux;
    while (!PilhaVazia(*pP)) {
        Desempilhar(pP, &aux);
    }
}

void Destruir(Pilha *pP) {
    EsvaziarP(pP);
}

int main() {
    Pilha minhaPilha = InicializarP();
    TipoDado valorRecuperado;

    printf("--- Testando o Empilhamento (Push) ---\n");
    printf("Empilhando 10.5...\n");
    Empilhar(&minhaPilha, 10.5);

    printf("Empilhando 20.3...\n");
    Empilhar(&minhaPilha, 20.3);

    printf("Empilhando 30.8...\n");
    Empilhar(&minhaPilha, 30.8);

    printf("\n--- Espiando o Topo ---\n");
    if (AcessarTopoP(minhaPilha, &valorRecuperado) == 0) {
        printf("O elemento atual no topo eh: %.1f\n\n", valorRecuperado);
    }

    printf("--- Testando o Desempilhamento (Pop) ---\n");
    while (!PilhaVazia(minhaPilha)) {
        Desempilhar(&minhaPilha, &valorRecuperado);
        printf("Desempilhado com sucesso: %.1f\n", valorRecuperado);
    }

    Destruir(&minhaPilha);
    printf("\nMemoria da pilha liberada com sucesso.\n");

    return 0;
}