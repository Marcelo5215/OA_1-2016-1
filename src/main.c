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
	
	free(CP);

	intercalaListasPrimario((char*)"lista1.txt", (char*)"lista2.txt");

	return 0;
}
