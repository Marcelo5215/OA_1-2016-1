#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

int main(int agrc, char** argv){
	indexI* CP = criaIndice((char*)"lista2.txt");
	imprimeIndice(CP);
	ordenaIndice(CP, 0, 21);
	printf("Sorted:\n");
	imprimeIndice(CP);
	free(CP);
	
	printf("lista 1:\n");
	CP = criaIndice((char*)"lista1.txt");
	imprimeIndice(CP);
	ordenaIndice(CP, 0, 19);
	printf("Sorted:\n");
	imprimeIndice(CP);
	free(CP);


	return 0;
}