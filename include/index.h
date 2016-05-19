#ifndef H_INDEX
#define H_INDEX

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#define TAM_REG 64

	typedef struct index_P indexI;

	int primeiroElementoIndicePrimario(indexI *ind);
	int ultimoElementoIndicePrimario(indexI *ind);

	indexI* criaIndicePrimario(char* nomeArq);
	void ordenaIndicePrimario(indexI* ind, int esquerda, int direita);
	void imprimeIndicePrimario(indexI* ind);
	char* getRegistroPrimario(FILE* fp, long int byte_offset);
	void intercalaListasPrimario(char* lista1, char* lista2);

#endif
