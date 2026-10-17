#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
int main(){
	int eh_digrafo = 0;
	Grafo* gr = cria_Grafo(6, 6, 1);

	insereAresta(gr, 0, 1, eh_digrafo, 6);
	insereAresta(gr, 0, 2, eh_digrafo, 1);
	insereAresta(gr, 0, 3, eh_digrafo, 5);
	insereAresta(gr, 1, 2, eh_digrafo, 2);
	insereAresta(gr, 1, 4, eh_digrafo, 5);
	insereAresta(gr, 2, 3, eh_digrafo, 2);
	insereAresta(gr, 2, 4, eh_digrafo, 6);
	insereAresta(gr, 2, 5, eh_digrafo, 4);
	insereAresta(gr, 3, 5, eh_digrafo, 4);
	insereAresta(gr, 4, 5, eh_digrafo, 3);

	int i, pai[6];
	arvoreGeradoraMinimaPrim_Grafo(gr, 0, pai);
	//arvoreGeradoraMinimaKruskal_Grafo(gr, 0, pai);

	imprime_Grafo(gr);

	for (i=0; i < 6; i++)
		printf("%d: pai = %d\n", i, pai[i]);

	libera_Grafo(gr);

	system("pause");
	return 0;
}
