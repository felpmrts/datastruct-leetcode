#ifndef FILA_H
#define FILA_H

typedef int TipoDado;

typedef struct {
    int num_elem_max;
    int indice_cabeca, indice_queue;
    TipoDado *tab;
} Fila;

Fila Inicializar();
int FilaVazia(Fila F);
int FilaCheia(Fila F);
int Enfileirar(Fila *F, TipoDado elem);
int Desenfileirar(Fila *F, TipoDado *elem);
void Esvaziar(Fila *F);
void ImprimirFila(Fila F, char tipo);

#endif // FILA_H
