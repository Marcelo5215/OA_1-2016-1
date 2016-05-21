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
	imprimeIndicePrimarioArq(CP, (char*)"indicelista2.ind");
	free(CP);
	
	printf("lista 1:\n");
	CP = criaIndicePrimario((char*)"lista1.txt");
	imprimeIndicePrimario(CP);
	ordenaIndicePrimario(CP, primeiroElementoIndicePrimario(CP), ultimoElementoIndicePrimario(CP));
	printf("Sorted:\n");
	imprimeIndicePrimario(CP);
	imprimeIndicePrimarioArq(CP, (char*)"indicelista1.ind");

	findRegistroPrimario("lista1.txt", CP, "042728DanielAlonsoNegrini      "); //lista errada -> nao existe
	findRegistroPrimario("lista1.txt", CP, "042865DaniloSilvaMarshall      "); //meio da lista
	findRegistroPrimario("lista1.txt", CP, "046961VitorPauloVillarinoPinto "); //fim da lista
	findRegistroPrimario("lista1.txt", CP, "035830RogerioAugustodeCastroNev"); //meio da lista + nome cortado
	findRegistroPrimario("lista1.txt", CP, "024312LeonardoNunesdeSouza     "); //inicio da lista
	findRegistroPrimario("lista1.txt", CP, "035830RogerioAugustodeCastroNex"); //ultimo caracter errado -> nao existe
	
	CP = incluirRegistroPrimario("lista1.txt", CP,
		"151234 Bernardo Nandes da Silva                 22  EM       C");
	CP = incluirRegistroPrimario("lista1.txt", CP,
		"000000 Fernando Costa da Silva                  99  CC       B");
	CP = incluirRegistroPrimario("lista1.txt", CP,
		"044442 Blabla blabla blabla bla                 99  CC       B");
// 	return 0;
	imprimeIndicePrimario(CP);
	
	free(CP);

	intercalaListasPrimario((char*)"lista1.txt", (char*)"lista2.txt");

	printf("Indice Secundario baseado em Cursos\n");
	indexS* CS = criaIndiceSecundario((char*)"lista1.txt", 0);
	imprimeIndiceSecundario(CS);

	limpaIndiceSecundario(CS);

	return 0;
}
