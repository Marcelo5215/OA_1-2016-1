#include "index.h"

#define FIM_IND "final"

struct index_P{
	char key[31];
	long int byte_offset;
	int tamanho;
};

/* Cria um indice a partir de um arquivo do modo especificado:      *
 * MATRIC       NOME                      OP   CURSO  TURMA         *                    
 * 150016794    Marcelo de Araujo Lopes   00    EC      A           *
 * com uma chave primaria que e a concatenacao dos campos matricula *
 * e nome.                                                          */
indexI* criaIndice(char* nomeArq){
	FILE* fp;
	fp = fopen(nomeArq, "r+");


	char stringAUX[64];      //servira apenas para ler as linhas do arquivo
	char chave[31];          //servira para adotarmos a chave primaria de cada registro
	long int byte_offset = 0;
	int tam_indice = 1 , i, j;        //tamanho atual do indice
	
	indexI* CP = (indexI*)malloc(sizeof(indexI));    //indice de Chaves Primarias
	CP[0].tamanho = 0;
	while(fscanf(fp,"%[^\n]\n", stringAUX) > 0){
		for (i = 0; i < 31; ++i){
			chave[i] = ' ';
		}
		chave[31] ='\0';
		//adquiri e concatena os campos para fazer a chave primaria
		i=0; j=0;
		while(i < 31){
			if(stringAUX[j] != ' '){
				chave[i] = stringAUX[j];
				i++; j++;
			}
			else if(stringAUX[j] == ' ' && stringAUX[j+1] == ' '){
				break;
			}
			else
				j++;
		}
		chave[31] ='\0';

		//atribui os valores ao indice
		CP[tam_indice-1].byte_offset = byte_offset;
		strcpy(CP[tam_indice-1].key, chave);
		CP[0].tamanho++;
		tam_indice++; 

		//aloca mais um espaco para o proximo registro no indice 
		CP = (indexI*)realloc(CP, sizeof(indexI)*tam_indice);
		//calcula o byte_offset do prox
		byte_offset = byte_offset + TAM_REG;

// 		fgetc(fp);
	}
	//um espaco será sempre alocado a mais, agora usaremos ele para indicar o final...
	strcpy(CP[tam_indice-1].key, FIM_IND);

	fclose(fp);

	return CP;
}

//imprime o indice
void imprimeIndice(indexI* ind){
	int i=0;

	while(strcmp(ind[i].key, FIM_IND) != 0){
		printf("%s --- %10ld\n", ind[i].key, ind[i].byte_offset);
		i++;
	}
	printf("%s--- %10.ld\n", ind[i].key, ind[i].byte_offset);
}

//ordena o indice primario com o mecanismmo do quicksort recursivo
void ordenaIndice(indexI* ind, int esquerda, int direita){
	if(direita >  ind[0].tamanho){
		printf("Tamanho inadequado.\n");
		return;
	}
	int i = esquerda, j = direita;
	char pivo[31];
	strcpy(pivo, ind[esquerda].key);
	indexI temp;

	while(j >= i){
		while(strcmp(ind[i].key, pivo) < 0){
			i++;
		}
		while(strcmp(ind[j].key, pivo) > 0){
			j--;
		}
		if(j >= i){
			temp = ind[i];
			ind[i] = ind[j];
			ind[j] = temp;
			i++;
			j--;
		}
	};
	if(j > esquerda){
		ordenaIndice(ind, esquerda, j);
	}
	if(i < direita){
		ordenaIndice(ind, i, direita);
	}
}

#undef FIM_IND
