#ifndef LISTA_H
#define LISTA_H

// Definição dos tipos
typedef float TipoDado; 

typedef struct Cell {
    TipoDado dado; 
    struct Cell *seguinte; 
} TipoCelula; 

// Protótipos das funções
void impDado(TipoDado dado); 
TipoDado LeituraDado(void); 
TipoCelula* InsCabL(TipoCelula *antigaL, TipoDado valor); 
TipoCelula* InsFimL(TipoCelula *L, TipoDado dado); 
TipoCelula* CriacaoListaInvertida(void); 
TipoCelula* CriacaoLista(void); 
void LiberacaoL(TipoCelula **pL); 
void ImprimeL(TipoCelula* L); 

#endif