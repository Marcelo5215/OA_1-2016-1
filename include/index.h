#ifndef H_INDEX
#define H_INDEX

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#define TAM_REG 64

	typedef struct index_P indexI;

	indexI* criaIndice(char* nomeArq);
	void imprimeIndice(indexI* ind);


#endif