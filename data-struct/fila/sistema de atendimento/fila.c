#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila Inicializar() {
    Fila filavazia;
    filavazia.indice_cabeca = 1;
    filavazia.indice_queue = 0;
    filavazia.num_elem_max = 100; 
    filavazia.tab = (TipoDado*)malloc(filavazia.num_elem_max * sizeof(TipoDado));
    return filavazia;
}

int FilaVazia(Fila F) {

    if (F.indice_cabeca == (F.indice_queue + 1) % F.num_elem_max)
        return 1;
    else
        return 0;
}

int FilaCheia(Fila F) {
    
    if (F.indice_cabeca == (F.indice_queue + 2) % F.num_elem_max)
        return 1;
    else
        return 0;
}

int Enfileirar(Fila *F, TipoDado elem) {
    if (FilaCheia(*F))
        return 1; 
    F->indice_queue++; 
    if (F->indice_queue == F->num_elem_max)
        F->indice_queue = 0; 
    F->tab[F->indice_queue] = elem;
    return 0;
}

int Desenfileirar(Fila *F, TipoDado *elem) {
    if (FilaVazia(*F))
        return 1;
    *elem = F->tab[F->indice_cabeca++]; 
    if (F->indice_cabeca == F->num_elem_max)
        F->indice_cabeca = 0;
    return 0;
}

void Esvaziar(Fila *F) {
    F->indice_cabeca = 1; 
    F->indice_queue = 0;
}

void ImprimirFila(Fila F, char tipo) {
    if (tipo == 'P') {
        printf("Fila Prioritária\n");
    } else if (tipo == 'N') {
        printf("Fila Normal\n");
    }
    
    TipoDado elem;
    
    while (!FilaVazia(F)) {
        Desenfileirar(&F, &elem);
        printf("%c%03d\n", tipo, elem);
    }
    printf("\n");
}
