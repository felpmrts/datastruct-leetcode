#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void impDado(TipoDado dado) {
    printf("%f", dado);
}

TipoDado LeituraDado(void) {
    TipoDado dado;
    scanf("%f", &dado);

    return dado;
}

TipoCelula* InsCabL(TipoCelula *antigaL, TipoDado valor) {
    TipoCelula *novaL;
    novaL = (TipoCelula*) malloc(sizeof(TipoCelula));

    novaL->dado = valor;
    novaL->seguinte = antigaL;

    return novaL;
}

TipoCelula* InsFimL(TipoCelula *L, TipoDado dado) {
    TipoCelula *p;       
    TipoCelula *novo;    
    
    novo = (TipoCelula*) malloc(sizeof(TipoCelula)); 
    novo->dado = dado;                               
    novo->seguinte = NULL;                          
    
    if (L == NULL) { 
        L = novo; 
    } else {
        
        p = L; 
        
        while (p->seguinte != NULL) {
            p = p->seguinte; 
        }
        
        p->seguinte = novo; 
    }
    
    return L; 
}

TipoCelula* CriacaoListaInvertida() {
    char escolha;
    TipoDado dado;
    TipoCelula *L = NULL; 
    
    printf("Deseja criar uma lista? (s/n): ");
    escolha = getchar();  
    getchar();            
    
    while (escolha == 's' || escolha == 'S') {
        printf("Fornecer um dado!: ");
        dado = LeituraDado(); 
        getchar();            
        
        L = InsCabL(L, dado); 
        
        printf("Inserir mais uma celula na frente da Lista? (s/n): ");
        escolha = getchar();  
        getchar();            
    }
    
    return L; 
}

TipoCelula* CriacaoLista() {

    char escolha;
    TipoDado dado;
    TipoCelula *L = NULL;

    puts("Deseja criar uma Lista? >> ");
    escolha = getchar();
    getchar();

    while(escolha == 's' || escolha == 'S') {
        puts("Fornecer um dado! >> ");
        dado = LeituraDado();
        getchar();

        L = InsFimL(L, dado);
        puts("Inserir mais uma célula no final da lista? (s/n) >> ");
        escolha = getchar();
        getchar();
    }

    return L;
}

void LiberacaoL(TipoCelula **pL) { 
    TipoCelula *p; 
     
    while (*pL != NULL) {
        p = *pL;           
        *pL = (*pL)->seguinte; 
        free(p);          
    }
}


void ImprimeL(TipoCelula* L) {
    TipoCelula *p = L; 
    while (p != NULL) { 
        printf("[%.1f] -> ", p->dado);
        p = p->seguinte; 
    }
    printf("NULL");
}