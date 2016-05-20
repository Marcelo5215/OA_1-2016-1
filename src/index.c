#include "index.h"

#define FIM_IND "final"

//estrutura para o indice primario
struct index_P{
	char key[31];
	long int byte_offset;
	int tamanho;
};

//estruturas para o indice secudario
typedef struct labels{
	char chave[31];
	int pont;
}labels;

struct indexS_P{
	labels *CS;
	labels *Lab;
	int tamanhoC, tamanhoL;
};

//FUNCOES PARA TRATAR INDICES PRIMARIOS

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

//cria um arquivo com os indices primarios
void imprimeIndicePrimarioArq(indexI* ind, char* nomeArq){
	FILE *fp = fopen(nomeArq, "w");

	for(int i = 0 ; i < ultimoElementoIndicePrimario(ind) ; i++){
		fprintf(fp, "%s       %10ld\n", ind[i].key, ind[i]. byte_offset);
	}

	fclose(fp);
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

//procura pelo registro com determinada chave, busca binaria
void findRegistroPrimario(char *nomeArq, indexI* ind, char *chave_primaria) {
	FILE *fp = fopen(nomeArq, "r");
	char string[64];
	int i, j;
	if (fp == NULL) {
		printf("Arquivo inexistente\n");
		return;
	}
	
	i = primeiroElementoIndicePrimario(ind);
	j = ultimoElementoIndicePrimario(ind);
	
	while (i < j) {
		int meio = (i + j) / 2;
		
		if (strcmp(ind[meio].key, chave_primaria) == 0) {
			fseek(fp, ind[meio].byte_offset, SEEK_SET);
			fscanf(fp, "%[^\n]\n", string);
			printf("%s\n", string);
			return;
		} else if (strcmp(ind[meio].key, chave_primaria) < 0) {
			i = meio + 1;
		} else {
			j = meio - 1;
		}
	}
	
	if(strcmp(ind[j].key, chave_primaria) == 0) {
		fseek(fp, ind[i].byte_offset, SEEK_SET);
		fscanf(fp, "%[^\n]\n", string);
		printf("%s\n", string);
		return;
	}
	printf("Nao existe essa chave\n");
	return;
}

//retorna a string correspondente ao regidtro na posição desejada
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

//FUNÇÕES PARA TRATAR INDICES SECUNDARIOS

indexS* criaIndiceSecundario(char* nomeArq, int OP){
	FILE *fp = fopen(nomeArq, "r");
	indexS* IS = (indexS*)malloc(sizeof(indexS));
	IS->CS = (labels*)malloc(sizeof(labels));
	IS->Lab = (labels*)malloc(sizeof(labels));

	char string[64];
	char chave[31], chaveSe[31];
	int i, j, Lab_count = 1, CS_count = 1;
	int flag = 0;
	while(fscanf(fp, "%[^\n]\n", string) > 0){
		for (i = 0; i < 31; ++i){
			chave[i] = ' ';
		}
		chave[31] ='\0';
		//adquiri e concatena os campos para fazer a chave primaria
		i=0; j=0;
		while(i < 31){
			if(string[j] != ' '){
				chave[i] = string[j];
				i++; j++;
			}
			else if(string[j] == ' ' && string[j+1] == ' '){
				break;
			}
			else
				j++;
		}
		chave[31] ='\0';

		//monta a chave secundaria
		switch(OP){
			case 0:
				chaveSe[0] = string[52];
				chaveSe[1] = string[53];
				chaveSe[2] = '\0';
				break;
			default:
				exit(0);
		}
		
		//atribui a nova chave secundaria e sua respectiva chave primaria
		strcpy(IS->Lab[Lab_count-1].chave, chave);
		flag = 0;
		//verifica se ja existe tal chave Secundaria
		for(i=0; i < CS_count && flag < 1; i++){
			if(strcmp(IS->CS[i].chave, chaveSe) == 0){
				flag = 1;
			}
		}
		if(!flag){
			strcpy(IS->CS[CS_count-1].chave, chaveSe);
			IS->CS[CS_count-1].pont = Lab_count-1;
			CS_count++;
// 			IS->Lab[Lab_count-1].pont = Lab_count-1;
			IS->Lab[Lab_count-1].pont = -1;
			Lab_count++;
		}
		else{//monta os ponteiros das chavesP
			i= IS->CS[i-1].pont;
			/*do{
				i = IS->Lab[i].pont;
			}while(IS->Lab[i].pont != -1 );*/
			while (IS->Lab[i].pont != -1 ) {
				i = IS->Lab[i].pont;
			}
			IS->Lab[i].pont = Lab_count-1;
// 			IS->Lab[Lab_count-1].pont = Lab_count-1;
			IS->Lab[Lab_count-1].pont = -1;
			Lab_count++; 
		}	

		//aloca mais espaço para o proximo
		IS->CS = (labels*)realloc(IS->CS, sizeof(labels)*CS_count);
		IS->Lab = (labels*)realloc(IS->Lab, sizeof(labels)*Lab_count);
	}
	strcpy(IS->CS[CS_count-1].chave, FIM_IND);
	strcpy(IS->Lab[Lab_count-1].chave, FIM_IND);

	IS->tamanhoC =  CS_count-1;
	IS->tamanhoL =  Lab_count-1;

	fclose(fp);
	return(IS);
}

void imprimeIndiceSecundario(indexS* ind){
	int i=0;
	while(i < ind->tamanhoC){
		printf("%s - %4d\n", ind->CS[i].chave, ind->CS[i].pont);
		i++;
	}
	printf("\n");
	i=0;
	while(i < ind->tamanhoL){
		printf("%s - %4d\n", ind->Lab[i].chave, ind->Lab[i].pont);
		i++;
	}
}

void limpaIndiceSecundario(indexS* ind){
	free(ind->CS);
	free(ind->Lab);
	free(ind);
}

#undef FIM_IND
