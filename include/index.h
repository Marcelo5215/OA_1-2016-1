#ifndef H_INDEX
#define H_INDEX

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#define TAM_REG 64

	typedef struct index_P indexI;

	int primeiroElementoIndice(indexI *ind);
	int ultimoElementoIndice(indexI *ind);

	indexI* criaIndice(char* nomeArq);
	void ordenaIndice(indexI* ind, int esquerda, int direita);
	void imprimeIndice(indexI* ind);
	char* getRegistro(FILE* fp, long int byte_offset);
	void intercalaListas(char* lista1, char* lista2);

#endif
