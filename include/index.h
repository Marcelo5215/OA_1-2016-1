#ifndef H_INDEX
#define H_INDEX

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#define TAM_REG 64

	struct tableindex_P;
	typedef struct tableindex_P tabelaInd_Prim;

	int primeiroElementoIndicePrimario(tabelaInd_Prim *ind);
	int ultimoElementoIndicePrimario(tabelaInd_Prim *ind);

	tabelaInd_Prim* criaIndicePrimario(char* nomeArq);
	void ordenaIndicePrimario(tabelaInd_Prim* ind, int esquerda, int direita);
	void imprimeIndicePrimario(tabelaInd_Prim* ind);
	char* getRegistroPrimario(FILE* fp, long int byte_offset);
	void intercalaListasPrimario(char* lista1, char* lista2);

#endif
