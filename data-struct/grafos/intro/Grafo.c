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

void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado){
	int i, vert, NV, cont = 1;
	int *fila, IF = 0, FF = 0; // IF/FF: início/final da fila
	
	// marca os vértices como não-visitados
	for(i=0; i<gr->nro_vertices; i++)
		visitado[i] = 0;

	// Cria a fila; visita e insere "ini" na mesma.
	NV = gr->nro_vertices;
	fila = (int*) malloc(NV * sizeof(int));
	FF++;
	fila[FF] = ini;
	visitado[ini] = cont;
	while(IF != FF){
		// toma o primeiro da fila
		IF = (IF + 1) % NV;
		vert = fila[IF];
		
		//cont++;
		
		// visita os vizinhos ainda não visitados, colocando-os na fila
		for(i=0; i<gr->grau[vert]; i++){
			if(!visitado[gr->arestas[vert][i]]){
				FF = (FF + 1) % NV;
				fila[FF] = gr->arestas[vert][i];
				visitado[gr->arestas[vert][i]] = ++cont;
			}
		}
	}
	free(fila);
}

void buscaProfundidade(Grafo *gr, int ini, int *visitado, int *cont){ // http://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs1.html
	int i;
	
	// marca o vértice como visitado; visita os vizinhos ainda não visitados.
	visitado[ini] = *cont;
	(*cont)++;
	for(i=0; i<gr->grau[ini]; i++){
		if(!visitado[gr->arestas[ini][i]])
			buscaProfundidade(gr,gr->arestas[ini][i],visitado,cont);
	}
}

void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado){
	int i, cont = 1;
	for(i=0; i<gr->nro_vertices; i++)
		visitado[i] = 0;
	buscaProfundidade(gr,ini,visitado,&cont);
	//for(i=0; i < gr->nro_vertices; i++)
	//    printf("%d -> %d\n",i,visitado[i]);
}

int procuraMenorDistancia(float *dist, int *visitado, int NV){
	int i, menor = -1, primeiro = 1;
	for (i=0; i < NV; i++){
		// procura vértice com menor distância e que não tenha sido visitado
		if (dist[i] >= 0 && visitado[i] == 0){
			if(primeiro){
				menor = i;
				primeiro = 0;
			} else {
				if (dist[menor] > dist[i])
					menor = i;
			}
		}
	}
	return menor;
}

void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist){
	int i, cont, NV, ind, *visitado, vert;
	cont = NV = gr->nro_vertices;
	
	// cria vetor auxiliar. Inicializa distâncias e anteriores
	visitado = (int*) malloc(NV * sizeof(int));
	for(i=0; i < NV; i++){
		ant[i] = -1;
		dist[i] = -1;
		visitado[i] = 0;
	}
	dist[ini] = 0;
	
	// procura vértice com menor distância e o marca como visitado
	while(cont > 0){
		vert = procuraMenorDistancia(dist, visitado, NV);
		//printf("u = %d\n",u);
		if(vert == -1)
			break;

		visitado[vert] = 1;
		cont--;
		
		for(i=0; i<gr->grau[vert]; i++){ // para cada vértice vizinho
			ind = gr->arestas[vert][i];
			// atualiza distâncias dos vizinhos
			if(dist[ind] < 0){
				 dist[ind] = dist[vert] + 1;//ou peso da aresta
				 ant[ind] = vert;
			}else{
				if(dist[ind] > dist[vert] + 1){
					dist[ind] = dist[vert] + 1;//ou peso da aresta
					ant[ind] = vert;
				}
			}
		}
	}

	free(visitado);
}

/*
Algoritmos para Grafos em C
 via Sedgewick
http://www.ime.usp.br/~pf/algoritmos_para_grafos/
*/
// https://www.cs.auckland.ac.nz/software/AlgAnim/dijkstra.html
// http://www.cprogramming.com/tutorial/computersciencetheory/dijkstra.html
//int procuraMenorDistancia(float *dist, int *visitado, int NV){
//void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist){

// http://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs1.html
//void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont){
//void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado){

// http://en.wikipedia.org/wiki/Breadth-first_search
// http://www.princeton.edu/~achaney/tmve/wiki100k/docs/Breadth-first_search.html
//void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado){

/* OUTRA VERSÃO
void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado){
	int i, vert, NV, cont = 1;
	int *pilha, IP = 0, FP = 0;
	for(i=0; i<gr->nro_vertices; i++)
		visitado[i] = 0;

	NV = gr->nro_vertices;
	pilha = (int*) malloc(NV * sizeof(int));
	FP++;
	pilha[FP] = ini;
	while(IP != FP){
		IP = (IP + 1) % NV;
		vert = pilha[IP];
		if(!visitado[vert]){
			visitado[vert] = cont;
			cont++;
			for(i=0; i<gr->grau[vert]; i++){
				if(!visitado[gr->arestas[vert][i]]){
					FP = (FP + 1) % NV;
					pilha[FP] = gr->arestas[vert][i];
				}
			}
		}
	}
	free(pilha);
	for(i=0; i < gr->nro_vertices; i++)
		printf("%d -> %d\n",i,visitado[i]);
}
*/

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
