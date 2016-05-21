#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

int main(int agrc, char** argv){
	
	printf("\tlista 2:\n");
	tabelaInd_Prim* CP = criaIndicePrimario((char*)"lista2.txt");
	imprimeIndicePrimario(CP);
	ordenaIndicePrimario(CP, primeiroElementoIndicePrimario(CP), ultimoElementoIndicePrimario(CP));
	printf("\tSorted:\n");
	imprimeIndicePrimario(CP);
	imprimeIndicePrimarioArq(CP, (char*)"indicelista2.ind");
	free(CP);
	
	printf("\tlista 1:\n");
	CP = criaIndicePrimario((char*)"lista1.txt");
	imprimeIndicePrimario(CP);
	ordenaIndicePrimario(CP, primeiroElementoIndicePrimario(CP), ultimoElementoIndicePrimario(CP));
	printf("\tSorted:\n");
	imprimeIndicePrimario(CP);
	imprimeIndicePrimarioArq(CP, (char*)"indicelista1.ind");

	CP = incluirRegistroPrimario("lista1.txt", CP,
		"151234 Bernardo Nandes da Silva                 22  EM       C");
	CP = incluirRegistroPrimario("lista1.txt", CP,
		"000000 Fernando Costa da Silva                  99  CC       B");
	CP = incluirRegistroPrimario("lista1.txt", CP,
		"044442 Blabla blabla blabla bla                 99  CC       B");

	printf("\tApos mais elementos:\n");
	imprimeIndicePrimario(CP);
	free(CP);

	intercalaListasPrimario((char*)"lista1.txt", (char*)"lista2.txt");

	indexS* IS = criaIndiceSecundario((char*)"lista1.txt", 0);
	imprimeIndiceSecundario(IS);

	limpaIndiceSecundario(IS);


	return 0;
}
