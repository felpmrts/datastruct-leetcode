#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h" //inclui os protótipos

//Definição do tipo Grafo
struct grafo{
	int eh_ponderado;
	int nro_vertices;
	int grau_max;  // tamanho das listas
	int** arestas; // array de arestas
	float** pesos;
	int* grau; // quantidade de elementos em cada lista
};

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado){
	Grafo *gr;
	gr = (Grafo*) malloc(sizeof(struct grafo));
	if(gr != NULL){
		int i;
		gr->nro_vertices = nro_vertices;
		gr->grau_max = grau_max;
		gr->eh_ponderado = (eh_ponderado != 0)?1:0;
		gr->grau = (int*) calloc(nro_vertices,sizeof(int));

		gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
		for(i=0; i<nro_vertices; i++)
			gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

		if(gr->eh_ponderado){
			gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
			for(i=0; i<nro_vertices; i++)
				gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
		}
	}
	return gr;
}

void libera_Grafo(Grafo* gr){
	if(gr != NULL){
		int i;

		// libera a matriz de arestas
		for(i=0; i<gr->nro_vertices; i++)
			free(gr->arestas[i]);
		free(gr->arestas);

		// libera a matriz de pesos
		if(gr->eh_ponderado){
			for(i=0; i<gr->nro_vertices; i++)
				free(gr->pesos[i]);
			free(gr->pesos);
		}
		free(gr->grau);
		free(gr);
	}
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
	if(gr == NULL)
		return 0;

	// verifica a existência dos vértices de origem e destino
	if(orig < 0 || orig >= gr->nro_vertices)
		return 0;
	if(dest < 0 || dest >= gr->nro_vertices)
		return 0;

	// insere aresta ao final da linha
	gr->arestas[orig][gr->grau[orig]] = dest;
	if(gr->eh_ponderado)
		gr->pesos[orig][gr->grau[orig]] = peso;
	gr->grau[orig]++;

	// insere a outra aresta se não for dígrafo
	if (eh_digrafo == 0)
		insereAresta(gr,dest,orig,1,peso);
	return 1;
}

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo){
	if(gr == NULL)
		return 0;
	if(orig < 0 || orig >= gr->nro_vertices)
		return 0;
	if(dest < 0 || dest >= gr->nro_vertices)
		return 0;

	// procura pela aresta
	int i = 0;
	while(i < gr->grau[orig] && gr->arestas[orig][i] != dest)
		i++;
	if(i == gr->grau[orig]) // elemento não encontrado
		return 0;
	gr->grau[orig]--;
	gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
	if(gr->eh_ponderado)
		gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
	if(eh_digrafo == 0)
		removeAresta(gr,dest,orig,1);
	return 1;
}

void arvoreGeradoraMinimaPrim_Grafo (Grafo *gr, int orig, int *pai) {
	int i, j, dest, primeiro, NV = gr->nro_vertices;
	double menorPeso;

	// vértices inicialmente não têm pai (exceto orig)
	for(i=0; i < NV; i++)
		pai[i] = -1; // sem pai
	pai[orig] = orig; // vértice inicial: raiz da AGM

	while (1){
		primeiro = 1;
		// percorre todos os vértices, e
		// Procura aresta de menor peso ligando um vértice
		// já na árvore a outro ainda não inserido
		for(i=0; i < NV; i++) {
			if (pai [i] != -1){ // vértice já inserido:
				// percorre-se seus vizinhos
				for(j=0; j<gr->grau[i]; j++) {
					int vizinho = gr->arestas[i][j];
					if (pai[vizinho] == -1){ // não inserido
						// busca aresta com menor peso
						if (primeiro) {
							menorPeso = gr->pesos[i][j];
							orig = i;
							dest = vizinho;
							primeiro = 0;
						} else {
							if (menorPeso > gr->pesos[i][j]){
								menorPeso = gr->pesos[i][j];
								orig = i;
								dest = vizinho;
							}
						}
					}
				}
			}
		}
		if (primeiro == 1)
			break;

		pai[dest] = orig;
	}
}

void arvoreGeradoraMinimaKruskal_Grafo (Grafo *gr, int orig, int *pai) {
	int i, j, dest, primeiro, NV = gr->nro_vertices;
	double menorPeso;
	int *arv = (int*) malloc(NV*sizeof(int));

	// cada vértice inicialmente é uma árvore sem pai
	for(i=0; i < NV; i++) {
		pai[i] = -1; // sem pai
		arv[i] = i;
	}
	pai[orig] = orig; // vértice inicial: raiz da AGM

	while (1){
		primeiro = 1;
		// percorre todos os vértices, e
		// Procura aresta de menor peso ligando
		// árvores diferentes
		for(i=0; i < NV; i++) {
			for(j=0; j<gr->grau[i]; j++) {
				int vizinho = gr->arestas[i][j];
				if (arv[i] != arv[vizinho]){ // não inserido
					// busca aresta com menor peso
					if (primeiro) {
						menorPeso = gr->pesos[i][j];
						orig = i;
						dest = vizinho;
						primeiro = 0;
					} else {
						if (menorPeso > gr->pesos[i][j]){
							menorPeso = gr->pesos[i][j];
							orig = i;
							dest = vizinho;
						}
					}
				}
			}
		}
		if (primeiro == 1)
			break;

		if (pai[orig] == -1)
			pai[orig] = dest;
		else
			pai[dest] = orig;

		// une as duas árvores da floresta selecionada
		for(i=0; i < NV; i++)
			if (arv[i] == arv[dest])
				arv[i] = arv[orig];
	}
	free(arv);
}

void imprime_Grafo(Grafo *gr){
	if(gr == NULL)
		return;

	int i, j;
	for(i=0; i < gr->nro_vertices; i++){
		printf("%d: ", i);
		for(j=0; j < gr->grau[i]; j++){
			if(gr->eh_ponderado)
				printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
			else
				printf("%d, ", gr->arestas[i][j]);
		}
		printf("\n");
	}
}
