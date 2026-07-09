#include <stdio.h>
#include <stdlib.h>

typedef float TipoDado;

typedef struct {
    int num_elem;
    int num_elem_max;
    TipoDado *tab;
} Pilha;

Pilha InicializarP(int num_max) {
    Pilha pilhavazia;
    pilhavazia.num_elem = 0;        
    pilhavazia.num_elem_max = num_max; 
    pilhavazia.tab = (TipoDado*) malloc(num_max * sizeof(TipoDado));
    return pilhavazia;
}

int PilhaVazia(Pilha P) {
    return (P.num_elem == 0) ? 1 : 0;
}

int PilhaCheia(Pilha P) {
    return (P.num_elem >= P.num_elem_max) ? 1 : 0;
}

int AcessarTopoP(Pilha P, TipoDado *pelem) {
    if (PilhaVazia(P)) {
        return 1; 
    }
    *pelem = P.tab[P.num_elem - 1]; 
    return 0; 
}

int Empilhar(Pilha* pP, TipoDado elem) {
    if (PilhaCheia(*pP)) {
        return 1; 
    }
    pP->tab[pP->num_elem] = elem; 
    pP->num_elem++;               
    return 0; 
}

int Desempilhar(Pilha *pP, TipoDado *pelem) {
    if (PilhaVazia(*pP)) {
        return 1; 
    }
    *pelem = pP->tab[pP->num_elem - 1]; 
    pP->num_elem--;                     
    return 0; 
}

void EsvaziarP(Pilha *pP) {
    pP->num_elem = 0; 
}

void Destruir(Pilha *pP) {
    if (pP->num_elem_max != 0) {
        free(pP->tab); 
    }
    pP->num_elem = 0;
    pP->num_elem_max = 0;
}

int main() {
    // 1. Criamos e inicializamos uma pilha com capacidade para até 3 elementos
    Pilha minhaPilha = InicializarP(3);
    TipoDado valorRecuperado;

    printf("--- Testando o Empilhamento (Push) ---\n");

    // 2. Vamos tentar colocar 3 elementos na nossa pilha
    printf("Empilhando 10.5...\n");
    Empilhar(&minhaPilha, 10.5); 

    printf("Empilhando 20.3...\n");
    Empilhar(&minhaPilha, 20.3); 

    printf("Empilhando 30.8...\n");
    Empilhar(&minhaPilha, 30.8); 

    // 3. O limite da pilha era 3. O que acontece se tentarmos colocar o quarto?
    // A função Empilhar vai retornar 1 (indicando o erro de pilha cheia)
    if (Empilhar(&minhaPilha, 40.0) == 1) { 
        printf("Aviso: Pilha cheia! Nao foi possivel empilhar o numero 40.0.\n\n"); 
    }


    printf("--- Espiando o Topo ---\n");

    // 4. Vamos olhar quem está no topo sem remover ninguém.
    // Como o 30.8 foi o último a entrar, ele deve estar no topo (Regra LIFO)
    if (AcessarTopoP(minhaPilha, &valorRecuperado) == 0) {
        printf("O elemento atual no topo eh: %.1f\n\n", valorRecuperado); 
    }


    printf("--- Testando o Desempilhamento (Pop) ---\n");

    // 5. Enquanto a pilha não estiver vazia, vamos retirando os elementos.
    // Repare que eles vão sair na ordem inversa à que entraram (30.8 -> 20.3 -> 10.5)
    while (!PilhaVazia(minhaPilha)) { 
        Desempilhar(&minhaPilha, &valorRecuperado); 
        printf("Desempilhado com sucesso: %.1f\n", valorRecuperado); 
    }

    printf("\n");


    // 6. Muito importante: Como usamos alocação dinâmica (malloc) dentro da inicialização,
    // precisamos liberar a memória antes do programa fechar para evitar vazamento de memória (memory leak).
    Destruir(&minhaPilha); 
    printf("Memoria da pilha liberada com sucesso.\n");

    return 0;
}