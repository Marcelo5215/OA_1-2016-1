#include "index.h"

#define FIM_IND "final"

struct LED_P {
	int PRR;
	int size;
	struct LED_P *next;
};

//estrutura para o indice primario
struct index_P{
	char key[31];
	long int byte_offset;
	int tamanho;
	LED *espac_disp;
};

//estruturas para o indice secundario
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
	
	indexI* CP = (indexI*) malloc(sizeof(indexI));    //indice de Chaves Primarias
	CP->espac_disp = NULL;
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
void ordenaIndicePrimario(indexI* ind, const int esquerda, const int direita){
// 	printf("ordenaIndicePrimario(%d,%d) %p\n", esquerda, direita, ind);
// 	printf("%d\n", ind->tamanho);
	if(direita >  ind->tamanho){
		printf("Tamanho inadequado.\n");
		return;
	}
	int i = esquerda, j = direita;
	char pivo[31];
	int ind_pivo;
	indexI temp;
	
	strcpy(pivo, ind[esquerda].key);
	ind_pivo = esquerda;
// 	printf("Pivo:%s\n", pivo);
	while(i <= j){
		while(strcmp(ind[i].key, pivo) <= 0){
// 			printf("i: %s->%d\n", ind[i].key, i);
			i++;
		}
		while(strcmp(ind[j].key, pivo) > 0){
// 			printf("j: %s->%d\n", ind[j].key, j);
			j--;
		}
		if(i <= j){
// 			printf("Troca: ");
// 			printf("i: %s->%d\t", ind[i].key, i);
// 			printf("j: %s->%d\n", ind[j].key, j);
			
			if (i == ind_pivo) {
				ind_pivo = j;
			} else if (j == ind_pivo) {
				ind_pivo = i;
			}
			
			temp = ind[i];
			ind[i] = ind[j];
			ind[j] = temp;
			i++;
			j--;
// 		imprimeIndicePrimario(ind);
		}
	}
	
// 	printf("(%d,%d)\n", i, j);
	
	temp = ind[i - 1];
	ind[i - 1] = ind[ind_pivo];
	ind[ind_pivo] = temp;
	ind_pivo = i - 1;
	j = ind_pivo - 1;
	i = ind_pivo + 1;
	
	if(j > esquerda){
// 		imprimeIndicePrimario(ind);
		ordenaIndicePrimario(ind, esquerda, j);
	}
	if(i < direita){
// 		imprimeIndicePrimario(ind);
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
	
	if(i == j && strcmp(ind[j].key, chave_primaria) == 0) {
		fseek(fp, ind[i].byte_offset, SEEK_SET);
		fscanf(fp, "%[^\n]\n", string);
		printf("%s\n", string);
		return;
	}
	printf("Nao existe essa chave\n");
	return;
}

//retorna a string correspondente ao registro na posição desejada
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

indexI *incluirRegistroPrimario (char *nomeArq, indexI *ind, char *registro) {
	
	LED *iterator, *prev = NULL;
	int t = strlen(registro);
	char chave_primaria[31];
	int i = 0, j = 0;
	FILE *fp;
	
	int posicao = 0;
	
	if (t != 62) {
		printf("Registro incompleto\n");
		return ind;
	}
	for (i = 0; i < 31; ++i){
		chave_primaria[i] = ' ';
	}
	i = 0;
	while(i < 31){
		if(registro[j] != ' '){
			chave_primaria[i] = registro[j];
			i++; j++;
		}
		else if(registro[j] == ' ' && registro[j+1] == ' '){
			break;
		}
		else
			j++;
	}
	chave_primaria[31] ='\0';
		
	
	//melhor ajuste
	//nao eh necessario, ja que os registros tem tamanho fixo
	for (iterator = ind->espac_disp; iterator != NULL; iterator = iterator->next) {
		if (iterator->size >= t) {
			fp = fopen(nomeArq, "a");
			
			//atualiza indexI *ind
			{
				i = primeiroElementoIndicePrimario(ind);
				j = ultimoElementoIndicePrimario(ind);
				
				while (i < j) {
					int meio = (i + j) / 2;
					
					if (strcmp(ind[meio].key, chave_primaria) == 0) {
						printf("ERRO: Chave primaria repetida\n");
						return ind;
					} else if (strcmp(ind[meio].key, chave_primaria) < 0) {
						i = meio + 1;
					} else {
						j = meio - 1;
					}
				}
				if (i == j) {
					if (strcmp(ind[i].key, chave_primaria) == 0) {
						printf("ERRO: Chave primaria repetida\n");
						return ind;
					} else if (strcmp(ind[i].key, chave_primaria) < 0) {
						int k = i + 1;
						indexI temp, move;
						ind = (indexI*) realloc(ind, sizeof(indexI) * (ind->tamanho + 2));
						
						if (k > ultimoElementoIndicePrimario(ind)) {
							strcpy(ind[i + 1].key, chave_primaria);
							ind[i + 1].byte_offset = iterator->PRR;
							
							strcpy(ind[i + 2].key, FIM_IND);
						} else {
							
							move = ind[k];
							
							for (k = i + 2; k <= ultimoElementoIndicePrimario(ind) + 1; k++) {
								temp = ind[k];
								ind[k] = move;
								move = temp;
							}
							ind[k] = move;
							
							strcpy(ind[i + 1].key, chave_primaria);
							ind[i + 1].byte_offset = iterator->PRR;
						}
						ind->tamanho++;
					} else {
						int k = i;
						indexI temp, move;
						ind = (indexI*) realloc(ind, sizeof(indexI) * (ind->tamanho + 2));
						
						move = ind[k];
						
						for (k = i + 1; k <= ultimoElementoIndicePrimario(ind) + 1; k++) {
							temp = ind[k];
							ind[k] = move;
							move = temp;
						}
						ind[k] = move;
						
						strcpy(ind[i + 1].key, chave_primaria);
						ind[i + 1].byte_offset = iterator->PRR;
						
						ind->tamanho++;
					}
				} else {
					int k = i;
					indexI temp, move;
					ind = (indexI*) realloc(ind, sizeof(indexI) * (ind->tamanho + 2));
					
					move = ind[k];
					
					for (k = i + 1; k <= ultimoElementoIndicePrimario(ind) + 1; k++) {
						temp = ind[k];
						ind[k] = move;
						move = temp;
					}
					ind[k] = move;
					
					strcpy(ind[i + 1].key, chave_primaria);
					ind[i + 1].byte_offset = iterator->PRR;
					
					ind->tamanho++;
				}
			}
			//atualiza arquivo
			fseek(fp, iterator->PRR, SEEK_SET);
			fprintf(fp, "%s\n", registro);
			
			//atualiza LED
			
			if (prev == NULL) {
				ind->espac_disp = iterator->next;
			} else {
				prev->next = iterator->next;
			}
			free(iterator);
			fclose(fp);
			return ind;
		}
		prev = iterator;
	}
	//sem espaco disponível
	
	fp = fopen(nomeArq, "a");
	
	//atualiza indexI *ind
	{
		i = primeiroElementoIndicePrimario(ind);
		j = ultimoElementoIndicePrimario(ind);
		
		while (i < j) {
			int meio = (i + j) / 2;
			
			if (strcmp(ind[meio].key, chave_primaria) == 0) {
				printf("ERRO: Chave primaria repetida\n");
				return ind;
			} else if (strcmp(ind[meio].key, chave_primaria) < 0) {
				i = meio + 1;
			} else {
				j = meio - 1;
			}
		}
		
		if (i == j) {
			if (strcmp(ind[i].key, chave_primaria) == 0) {
				printf("ERRO: Chave primaria repetida\n");
				return ind;
			} else if (strcmp(ind[i].key, chave_primaria) < 0) {
				int k = i + 1;
				indexI temp, move;
				
				ind = (indexI *) realloc(ind, sizeof(indexI) * (ind->tamanho + 2));
				
				if (k > ultimoElementoIndicePrimario(ind)) {
					strcpy(ind[i + 1].key, chave_primaria);
					ind[i + 1].byte_offset = ind->tamanho * TAM_REG;
					strcpy(ind[i + 2].key, FIM_IND);
				} else {
				
					move = ind[k];
					
					for (k = i + 2; k <= ultimoElementoIndicePrimario(ind) + 1; k++) {
						temp = ind[k];
						ind[k] = move;
						move = temp;
					}
					ind[k] = move;
					
					strcpy(ind[i + 1].key, chave_primaria);
					ind[i + 1].byte_offset = ind->tamanho * TAM_REG;
				}
				posicao = i + 1;
				ind->tamanho++;
			} else {
				int k = i;
				indexI temp, move;
				ind = (indexI*) realloc(ind, sizeof(indexI) * (ind->tamanho + 2));
				
				move = ind[k];
				
				for (k = i + 1; k <= ultimoElementoIndicePrimario(ind) + 1; k++) {
					temp = ind[k];
					ind[k] = move;
					move = temp;
				}
				ind[k] = move;
				
				strcpy(ind[i].key, chave_primaria);
				ind[i].byte_offset = ind->tamanho * TAM_REG;
				
				posicao = i;
				ind->tamanho++;
			}
		} else {
			int k = i;
			indexI temp, move;
			ind = (indexI*) realloc(ind, sizeof(indexI) * (ind->tamanho + 2));
			
			move = ind[k];
			
			for (k = i + 1; k <= ultimoElementoIndicePrimario(ind) + 1; k++) {
				temp = ind[k];
				ind[k] = move;
				move = temp;
			}
			ind[k] = move;
			
			strcpy(ind[i].key, chave_primaria);
			ind[i].byte_offset = ind->tamanho * TAM_REG;
			
			posicao = i;
			ind->tamanho++;
		}
	}
	
	//atualiza arquivo
	fseek(fp, ind[posicao].byte_offset, SEEK_SET);
	fprintf(fp, "%s\n", registro);
	fclose(fp);
	
	return ind;
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
		for(i=0; i < CS_count - 1 && flag < 1; i++){
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
