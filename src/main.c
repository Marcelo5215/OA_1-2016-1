#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

int main(int agrc, char** argv){
	char *lista1 = "lista1.txt";

	tabelaInd_Prim* IP = criaIndicePrimario(lista1);

	imprimeIndicePrimario(IP);
	retiraRegistroPrimario(lista1, IP, "041881 Ana Luisa Costa Miguel                   34  CC       A");
	imprimeIndicePrimario(IP);
	free(IP);

	
	printf("\tlista 2:\n");
	tabelaInd_Prim* CP = criaIndicePrimario((char*)"lista2.txt");
	imprimeIndicePrimario(CP);
	imprimeIndicePrimarioArq(CP, (char*)"indicelista2.ind");
	free(CP);
	
	printf("\tlista 1:\n");
	CP = criaIndicePrimario((char*)"lista1.txt");
	imprimeIndicePrimario(CP);
	
	CP = incluirRegistroPrimario("lista1.txt", CP,
		"151234 Bernardo Nandes da Silva                 22  EM       C");
	CP = incluirRegistroPrimario("lista1.txt", CP,
		"000000 Fernando Costa da Silva                  99  CC       B");
	CP = incluirRegistroPrimario("lista1.txt", CP,
		"044442 Blabla blabla blabla bla                 99  CC       B");

	printf("\tApos mais elementos:\n");
	imprimeIndicePrimario(CP);
	imprimeIndicePrimarioArq(CP, (char*)"indicelista1.ind");
	free(CP);

	intercalaListasPrimario((char*)"lista1.txt", (char*)"lista2.txt");

	indexS* IS = criaIndiceSecundario((char*)"lista1.txt", 0);
	imprimeIndiceSecundario(IS);

	limpaIndiceSecundario(IS);


	return 0;
}
