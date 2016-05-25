#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"

int main(int argc, char **argv){

	tabelaInd_Prim *CP = criaIndicePrimario((char *) "lista1.txt");
	indexS *IS = criaIndiceSecundario((char *)"lista1.txt", 0);

	printf("\tlista 1:\n");
	imprimeIndicePrimario(CP);
	imprimeIndiceSecundario(IS);
	
	printf("\tRetirada\n");
	retirarRegistro("lista1.txt", CP, IS,
		"041881 Ana Luisa Costa Miguel                   34  CC       A", 0);
	retirarRegistro("lista1.txt", CP, IS,
		"031272 Andreza Pollyana da Silva                32  EC       A", 0);
	
	imprimeIndicePrimario(CP);
	imprimeIndiceSecundario(IS);
	
	printf("\tAtualizacao\n");
	atualizarRegistro("lista1.txt", CP, IS,
		"043217 Erikita Regina Campos de Almeida         34  CC       A",
		"043217 Erikita Regina Campos de Almeida         34  EC       A");
	imprimeIndicePrimario(CP);
	imprimeIndiceSecundario(IS);
	
	printf("\tInclusao\n");
	incluirRegistro("lista1.txt", CP, IS,
		"000000 Fernando Costa da Silva                  99  CC       B", 0);
	incluirRegistro("lista1.txt", CP, IS,
		"044442 Blabla blabla blabla bla                 99  CC       B", 0);
	incluirRegistro("lista1.txt", CP , IS,
		"151234 Bernardo Nandes da Silva                 22  EM       C", 0);

	printf("\tApos mais elementos:\n");
	imprimeIndicePrimario(CP);
	imprimeIndiceSecundario(IS);
	imprimeIndicePrimarioArq(CP, (char*)"indicelista1.ind");

	intercalaListasPrimario((char*)"lista1.txt", (char*)"lista2.txt");

	limpaIndiceSecundario(IS);
	free(CP);


	/*
	printf("\tlista 2:\n");
	CP = criaIndicePrimario((char*)"lista2.txt");
	imprimeIndicePrimario(CP);
	imprimeIndicePrimarioArq(CP, (char*)"indicelista2.ind");
	free(CP);
	*/

	return 0;
}
