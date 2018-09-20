#include <stdio.h>
#include <string.h>

int verifica_padrao(char nome_arquivo[], char padrao_nome[]){
	
	unsigned short int auxiliar;
	
	int quantidade_TOTAL = strlen(padrao_nome);
	int quantidade_compara = strlen(nome_arquivo);
	
	char pra_comparar[strlen(nome_arquivo) + 1];
	
	if(quantidade_compara > quantidade_TOTAL){
		int j = 0;
		while(j < quantidade_TOTAL){
			pra_comparar[j] = nome_arquivo[quantidade_compara - quantidade_TOTAL + j];
			j = j + 1;
		}
	}
	
	else
		strcpy(pra_comparar, nome_arquivo);
	
	int i = 0;
	do{
		
		if( (pra_comparar[i] >= 48 && pra_comparar[i] <= 57) && (padrao_nome[i] >= 48 && padrao_nome[i] <= 57) )
			auxiliar = 0;
		else if(pra_comparar[i] == padrao_nome[i])
			auxiliar = 0;
		else
			return 1;
		i = i + 1;
	}while(padrao_nome[i] != '\0');

	return auxiliar;
}

int verifica_padr_ate(char nome_arquivo[], char padrao_nome[], char termino){
	
	unsigned short int auxiliar;
	
	int quantidade_TOTAL = strlen(padrao_nome);
	int quantidade_compara = strlen(nome_arquivo);
	
	char pra_comparar[strlen(nome_arquivo) + 1];
	
	if(quantidade_compara > quantidade_TOTAL){
		int j = 0;
		while(j < quantidade_TOTAL){
			pra_comparar[j] = nome_arquivo[quantidade_compara - quantidade_TOTAL + j];
			j = j + 1;
		}
	}
	
	else
		strcpy(pra_comparar, nome_arquivo);
	
	int i = 0;
	do{
		
		if( (pra_comparar[i] >= 48 && pra_comparar[i] <= 57) && (padrao_nome[i] >= 48 && padrao_nome[i] <= 57) )
			auxiliar = 0;
		else if(pra_comparar[i] == padrao_nome[i])
			auxiliar = 0;
		else
			return 1;
		i = i + 1;
	}while(padrao_nome[i] != termino);

	return auxiliar;
}

unsigned short int nomainus(char nome_arquivo[], char padrao_nome[], char termino){
	
	unsigned short int auxiliar;
	
	int quantidade_TOTAL = strlen(padrao_nome);
	int quantidade_compara = strlen(nome_arquivo);
	
	char pra_comparar[strlen(nome_arquivo) + 1];
	
	if(quantidade_compara > quantidade_TOTAL){
		int j = 0;
		while(j < quantidade_TOTAL){
			pra_comparar[j] = nome_arquivo[quantidade_compara - quantidade_TOTAL + j];
			j = j + 1;
		}
	}
	
	else
		strcpy(pra_comparar, nome_arquivo);
	
	int i = 0;
	do{
		
		if( (pra_comparar[i] >= 48 && pra_comparar[i] <= 57) && (padrao_nome[i] >= 48 && padrao_nome[i] <= 57) )
			auxiliar = 0;
		else if( (pra_comparar[i] == padrao_nome[i]) || (pra_comparar[i] == (padrao_nome[i] + 32)) || (pra_comparar[i] == (padrao_nome[i] - 32)) )
			auxiliar = 0;
		else
			return 1;
		i = i + 1;
	}while(padrao_nome[i] != termino);

	return auxiliar;
}
