#include <stdio.h>
#include <stdlib.h>

typedef float TipoDado; 

typedef struct Cell {
    TipoDado dada; 
    struct Cell * seguinte; 
} TipoCelula; 


void ImpDado(TipoDado dada) {
    printf("%.2f ", dada); 
}

TipoDado LeituraDado(void) {
    TipoDado dada;
    scanf("%f", &dada); 
    return dada; 
}

TipoCelula* InsCabL(TipoCelula *antigal, TipoDado dada) {
    TipoCelula *novaL; 
    
    novaL = (TipoCelula*)malloc(sizeof(TipoCelula)); 
    novaL->dada = dada; 
    novaL->seguinte = antigal; 
    return novaL; 
}

TipoCelula* CriacaoListaInvertida() {
    char escolha;
    TipoDado dada;
    TipoCelula *L = NULL; 
    
    puts("Deseja criar uma lista? (S/N)");
    escolha = getchar(); 
    getchar(); 

    while (escolha == 'S' || escolha == 's') { 
        puts("Fornecer um dado!");
        dada = LeituraDado(); 
        getchar(); 

        L = InsCabL(L, dada); 
        
        puts("Inserir mais uma celula na frente da Lista? (S/N)");
        escolha = getchar(); 
        getchar(); 
    }
    return L; 
}

void ImprimeL(TipoCelula* L) {
    TipoCelula *p;
    p = L; 
    
    while (p != NULL) { 
        ImpDado(p->dada); 
        p = p->seguinte; 
    }
    puts(""); 
}


TipoCelula* ConcatenaListas(TipoCelula* L1, TipoCelula* L2) {
    TipoCelula* p;

    if (L1 == NULL) {
        return L2;
    }

    p = L1;
    while (p->seguinte != NULL) {
        p = p->seguinte;
    }

    p->seguinte = L2;

    return L1;
}

int main(void) {
    TipoCelula *Lista1 = NULL;
    TipoCelula *Lista2 = NULL;
    TipoCelula *ListaConcatenada = NULL;

    printf("=== CRIACAO DA LISTA 1 ===\n");
    Lista1 = CriacaoListaInvertida();

    printf("\n=== CRIACAO DA LISTA 2 ===\n");
    Lista2 = CriacaoListaInvertida();

    printf("\nLista 1 digitada (Invertida): \n");
    ImprimeL(Lista1);

    printf("Lista 2 digitada (Invertida): \n");
    ImprimeL(Lista2);

    printf("\n=== CONCATENANDO AS LISTAS ===\n");
    ListaConcatenada = ConcatenaListas(Lista1, Lista2);

    printf("Lista Resultante da Concatenacao: \n");
    ImprimeL(ListaConcatenada);

    return 0;
}