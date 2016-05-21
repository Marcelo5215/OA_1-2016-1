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

	typedef struct index_P indexI;	// indice primario
	typedef struct indexS_P indexS; // indice secundario
	typedef struct LED_P LED; // Lista de espacos disponíveis


	int primeiroElementoIndicePrimario(indexI *ind);
	int ultimoElementoIndicePrimario(indexI *ind);

	indexI* criaIndicePrimario(char* nomeArq);
	void ordenaIndicePrimario(indexI* ind, int esquerda, int direita);
	void imprimeIndicePrimario(indexI* ind);
	void imprimeIndicePrimarioArq(indexI* ind, char* nomeArq);
	void findRegistroPrimario(char *nomeArq, indexI* ind, char *chave_primaria);
	void intercalaListasPrimario(char* lista1, char* lista2);
	
	void incluirRegistroPrimario (char *nomeArq, indexI *ind, char *registro);

	indexS* criaIndiceSecundario(char* nomeArq, int OP);
	void imprimeIndiceSecundario(indexS* ind);
	void limpaIndiceSecundario(indexS* ind);

#endif
