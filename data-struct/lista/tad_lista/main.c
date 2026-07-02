#include <stdio.h>
#include "lista.h"

int main(void) { 
    TipoCelula *lista1, *lista2; 

    // Criando as listas usando as funções do nosso TAD
    lista1 = CriacaoListaInvertida(); 
    lista2 = CriacaoLista(); 

    // Exibindo os resultados
    ImprimeL(lista1); 
    printf("\n");
    ImprimeL(lista2); 
    printf("\n");

    // Liberando a memória com segurança
    LiberacaoL(&lista1);
    LiberacaoL(&lista2); 

    return 0; 
}