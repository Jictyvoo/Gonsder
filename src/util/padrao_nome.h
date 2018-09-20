#ifndef COM_BR_HAGENIX_GAMES_UTIL_PADRAO_NOME_H
#define COM_BR_HAGENIX_GAMES_UTIL_PADRAO_NOME_H

#include <iostream>
#include <string>
using namespace std;

int verifica_padrao(string nome_arquivo, string padrao_nome){
	
	unsigned short int auxiliar;
	
	int quantidade_TOTAL = padrao_nome.size();
	int quantidade_compara = nome_arquivo.size();
	
	string pra_comparar(quantidade_compara + 1, '\0');

	if(quantidade_compara > quantidade_TOTAL){
		int j = 0;
		while(j < quantidade_TOTAL){
			pra_comparar[j] = nome_arquivo[quantidade_compara - quantidade_TOTAL + j];
			j = j + 1;
		}
	}
	
	else
		pra_comparar = nome_arquivo;
	
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

int verifica_padr_ate(string nome_arquivo, string padrao_nome, char termino){
	
	unsigned short int auxiliar;
	
	int quantidade_TOTAL = padrao_nome.size();
	int quantidade_compara = nome_arquivo.size();
	
	string pra_comparar(quantidade_compara + 1, '\0');
	
	if(quantidade_compara > quantidade_TOTAL){
		int j = 0;
		while(j < quantidade_TOTAL){
			pra_comparar[j] = nome_arquivo[quantidade_compara - quantidade_TOTAL + j];
			j = j + 1;
		}
	}
	
	else
		pra_comparar = nome_arquivo;
	
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

unsigned short int nomainus(string nome_arquivo, string padrao_nome, char termino){
	
	unsigned short int auxiliar;
	
	int quantidade_TOTAL = padrao_nome.size();
	int quantidade_compara = nome_arquivo.size();
	
	string pra_comparar(quantidade_compara + 1, '\0');
	
	if(quantidade_compara > quantidade_TOTAL){
		int j = 0;
		while(j < quantidade_TOTAL){
			pra_comparar[j] = nome_arquivo[quantidade_compara - quantidade_TOTAL + j];
			j = j + 1;
		}
	}
	
	else
		pra_comparar = nome_arquivo;
	
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

#endif /* COM_BR_HAGENIX_GAMES_UTIL_PADRAO_NOME_H */
