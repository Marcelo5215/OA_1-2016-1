#include "index.h"

#define FIM_IND "final"

struct index_P{
	char key[31];
	long int byte_offset;
	int tamanho;
};

int primeiroElementoIndicePrimario(indexI *ind) { return (ind == NULL) ? -1 : 0; }
//Há ind->tamanho elementos, de 0 até ind->tamanho -1, nao incluindo FIM_IND
//que não está incluido no tamanho
int ultimoElementoIndicePrimario(indexI *ind) { return (ind == NULL) ? -1 : ind->tamanho - 1; }

/* Cria um indice a partir de um arquivo do modo especificado:      *
 * MATRIC       NOME                      OP   CURSO  TURMA         *                    
 * 150016794    Marcelo de Araujo Lopes   00    EC      A           *
 * com uma chave primaria que e a concatenacao dos campos matricula *
 * e nome.                                                          */
indexI* criaIndicePrimario(char* nomeArq){
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
void imprimeIndicePrimario(indexI* ind){
	int i=0;

	while(strcmp(ind[i].key, FIM_IND) != 0){
		printf("%s --- %10ld\n", ind[i].key, ind[i].byte_offset);
		i++;
	}
	printf("%s\n", ind[i].key);
}

//ordena o indice primario com o mecanismmo do quicksort recursivo
void ordenaIndicePrimario(indexI* ind, int esquerda, int direita){
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
		ordenaIndicePrimario(ind, esquerda, j);
	}
	if(i < direita){
		ordenaIndicePrimario(ind, i, direita);
	}
} 

char* getRegistroPrimario(FILE* fp, long int byte_offset){
	static char saida[64];
	fseek(fp, byte_offset, SEEK_SET);
	fscanf(fp,"%[^\n]s", saida);

	return saida;
}

// cria um arquivo com as duas listas intercaladas
void intercalaListasPrimario(char* lista1, char* lista2){
	//arquivos a serem manipulados
	FILE *fp1, *fp2, *saida;
	fp1 = fopen(lista1, "r");
	fp2 = fopen(lista2, "r");
	saida = fopen("lista12.txt", "w");
	//indices das listas
	indexI* CP1 = criaIndicePrimario(lista1);
	indexI* CP2 = criaIndicePrimario(lista2);

	//ordena os indices
	ordenaIndicePrimario(CP1, primeiroElementoIndicePrimario(CP1), ultimoElementoIndicePrimario(CP1));
	ordenaIndicePrimario(CP2, primeiroElementoIndicePrimario(CP2), ultimoElementoIndicePrimario(CP2));

	//a partir dos indices une as listas
	int i = 0 , j = 0;
	while(strcmp(CP1[i].key, FIM_IND) != 0 && strcmp(CP2[j].key, FIM_IND) != 0){
		if(strcmp(CP1[i].key, CP2[j].key) < 0){
			fprintf(saida, "%s\n", getRegistroPrimario(fp1, CP1[i].byte_offset));
			i++;
		}
		else if(strcmp(CP2[j].key, CP1[i].key) < 0){
			fprintf(saida, "%s\n", getRegistroPrimario(fp2, CP2[j].byte_offset));
			j++;
		}
		else{
			fprintf(saida, "%s\n", getRegistroPrimario(fp2, CP2[j].byte_offset));
			i++; j++;
		}
	}
	// se algum dos dois não  chegou ao fim...
	if(strcmp(CP1[i].key, FIM_IND) == 0){
		while(strcmp(CP2[j].key, FIM_IND) != 0){
			fprintf(saida, "%s\n", getRegistroPrimario(fp2, CP2[j].byte_offset));
			j++;
		}
	} 
	else if(strcmp(CP2[j].key, FIM_IND) == 0){
		while(strcmp(CP1[i].key, FIM_IND) != 0){
			fprintf(saida, "%s\n", getRegistroPrimario(fp1, CP1[i].byte_offset));
			i++;
		}
	}

	fclose(fp1);
	fclose(fp2);
	fclose(saida);
	free(CP1);
	free(CP2);
}

#undef FIM_IND
