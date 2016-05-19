#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

int main(int agrc, char** argv){
	indexI* CP = criaIndice((char*)"lista2.txt");
	imprimeIndice(CP);
	ordenaIndice(CP, primeiroElementoIndice(CP), ultimoElementoIndice(CP));
	printf("Sorted:\n");
	imprimeIndice(CP);
	free(CP);
	
	printf("lista 1:\n");
	CP = criaIndice((char*)"lista1.txt");
	imprimeIndice(CP);
	ordenaIndice(CP, primeiroElementoIndice(CP), ultimoElementoIndice(CP));
	printf("Sorted:\n");
	imprimeIndice(CP);
	free(CP);

	intercalaListas((char*)"lista1.txt", (char*)"lista2.txt");


	return 0;
}
