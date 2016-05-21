#ifndef H_INDEX
#define H_INDEX

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#define TAM_REG 64	
	#define TAM_MATRIC 7
	#define TAM_NOME 41
	#define TAM_OP 4
	#define TAM_CURSO 9
	#define TAM_TURMA 1

	struct tableindex_P;
	typedef struct tableindex_P tabelaInd_Prim;
	typedef struct indexS_P indexS;

	int primeiroElementoIndicePrimario(tabelaInd_Prim *ind);
	int ultimoElementoIndicePrimario(tabelaInd_Prim *ind);

	tabelaInd_Prim* criaIndicePrimario(char* nomeArq);
	void ordenaIndicePrimario(tabelaInd_Prim* ind, int esquerda, int direita);
	void imprimeIndicePrimario(tabelaInd_Prim* ind);
	char* getRegistroPrimario(FILE* fp, long int byte_offset);
	void imprimeIndicePrimarioArq(tabelaInd_Prim* ind, char* nomeArq);
	void intercalaListasPrimario(char* lista1, char* lista2);

	tabelaInd_Prim* incluirRegistroPrimario (char *nomeArq, tabelaInd_Prim *ind, char *registro);

	indexS* criaIndiceSecundario(char* nomeArq, int OP);
	void imprimeIndiceSecundario(indexS* ind);
	void limpaIndiceSecundario(indexS* ind);

#endif
