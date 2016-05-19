#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

int main(int agrc, char** argv){
	indexI* CP = criaIndicePrimario((char*)"lista2.txt");
	imprimeIndicePrimario(CP);
	ordenaIndicePrimario(CP, primeiroElementoIndicePrimario(CP), ultimoElementoIndicePrimario(CP));
	printf("Sorted:\n");
	imprimeIndicePrimario(CP);
	free(CP);
	
	printf("lista 1:\n");
	CP = criaIndicePrimario((char*)"lista1.txt");
	imprimeIndicePrimario(CP);
	ordenaIndicePrimario(CP, primeiroElementoIndicePrimario(CP), ultimoElementoIndicePrimario(CP));
	printf("Sorted:\n");
	imprimeIndicePrimario(CP);
	free(CP);

	intercalaListasPrimario((char*)"lista1.txt", (char*)"lista2.txt");


	return 0;
}
