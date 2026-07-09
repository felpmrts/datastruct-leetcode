#include <stdio.h>
#include <stdlib.h>

typedef float TipoDado; 

typedef struct { 
    int num_elem_max;     /* Capacidade máxima do vetor */ 
    int indice_cabeca;    /* Índice de onde removemos (frente) */ 
    int indice_queue;     /* Índice de onde inserimos (fim) */
    TipoDado *tab;        /* O vetor que guardará os elementos */ 
} Fila; 

Fila InicializarF(int num_max) {
    Fila filavazia;
    filavazia.indice_cabeca = 1;
    filavazia.indice_queue = 0;
    filavazia.num_elem_max = num_max;
    filavazia.tab = (TipoDado*) malloc(num_max * sizeof(TipoDado));
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

char InserirF(Fila *pF, TipoDado elem) {
    if (FilaCheia(*pF))
        return 1;
    
    pF->indice_queue++;
    if (pF->indice_queue == pF->num_elem_max)
        pF->indice_queue = 0;
        
    pF->tab[pF->indice_queue] = elem;
    return 0;
}

char RemoverF(Fila *pF, TipoDado *pelem) {
    if (FilaVazia(*pF))
        return 1;
        
    *pelem = pF->tab[pF->indice_cabeca];
    pF->indice_cabeca++;
    
    if (pF->indice_cabeca == pF->num_elem_max)
        pF->indice_cabeca = 0;
        
    return 0;
}

int AcessarCabecaF(Fila F, TipoDado *pelem) {
    if (FilaVazia(F)) return 1;
    *pelem = F.tab[F.indice_cabeca];
    return 0;
}

void DestruirF(Fila *pF) {
    if (pF->num_elem_max != 0)
        free(pF->tab);
    pF->num_elem_max = 0;
}

int main() {
    /* Inicializa uma fila com capacidade para 5 espaços no vetor */
    /* Como a estratégia do professor reserva 1 espaço de segurança, a capacidade real é 4 elementos */
    Fila minhaFila = InicializarF(5); 
    TipoDado valorRemovido;
    TipoDado primeiroDaFila;

    printf("=== Testando Primitivas da Fila Circular ===\n\n");

    /* 1. Verificando se inicia vazia */
    if (FilaVazia(minhaFila)) {
        printf("Sucesso: A fila iniciou vazia (cabeca: %d, queue: %d).\n\n", minhaFila.indice_cabeca, minhaFila.indice_queue);
    }

    /* 2. Inserindo elementos até encher a capacidade útil (4 elementos) */
    printf("Inserindo elementos: 10.5, 20.0, 30.5, 40.0...\n");
    InserirF(&minhaFila, 10.5);
    InserirF(&minhaFila, 20.0);
    InserirF(&minhaFila, 30.5);
    InserirF(&minhaFila, 40.0);

    /* Espiando a cabeça da fila */
    if (AcessarCabecaF(minhaFila, &primeiroDaFila) == 0) {
        printf("Primeiro elemento atual na fila: %.1f\n", primeiroDaFila);
    }

    /* 3. Tentando forçar o estouro da fila (Inserir o 5º elemento) */
    printf("\nTentando inserir o 5o elemento (50.0) para testar FilaCheia...\n");
    if (InserirF(&minhaFila, 50.0) == 1) {
        printf("Fila Cheia detectada com sucesso! Impediu a insercao de 50.0.\n");
        printf("Estado dos indices -> cabeca: %d, queue: %d\n\n", minhaFila.indice_cabeca, minhaFila.indice_queue);
    }

    /* 4. Removendo dois elementos (o 10.5 e o 20.0 devem sair) */
    printf("Removendo 2 elementos...\n");
    if (RemoverF(&minhaFila, &valorRemovido) == 0) {
        printf("Removido: %.1f\n", valorRemovido);
    }
    if (RemoverF(&minhaFila, &valorRemovido) == 0) {
        printf("Removido: %.1f\n", valorRemovido);
    }
    printf("Estado dos indices apos remocoes -> cabeca: %d, queue: %d\n\n", minhaFila.indice_cabeca, minhaFila.indice_queue);

    /* 5. Provando a Circularidade: Como removemos 2 elementos, abriu espaço no início do vetor */
    /* Os novos elementos (60.0 e 70.0) vão dar a volta e ocupar os índices 0 e 1 do vetor */
    printf("Inserindo novos elementos (60.0 e 70.0) para testar a curva circular...\n");
    InserirF(&minhaFila, 60.0);
    InserirF(&minhaFila, 70.0);
    printf("Estado final dos indices -> cabeca: %d, queue: %d\n", minhaFila.indice_cabeca, minhaFila.indice_queue);

    /* 6. Esvaziando o que sobrou na fila */
    printf("\nDescarregando o restante da fila:\n");
    while (!FilaVazia(minhaFila)) {
        RemoverF(&minhaFila, &valorRemovido);
        printf("Removido: %.1f\n", valorRemovido);
    }

    /* 7. Liberando a memória alocada */
    DestruirF(&minhaFila);
    printf("\nFila destruida e memoria liberada.\n");

    return 0;
}