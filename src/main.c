#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

int main(int agrc, char** argv){
	indexI* CP = criaIndice((char*)"lista1.txt");

	imprimeIndice(CP);


	free(CP);
	return 0;
}