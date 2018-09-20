/*
 * UserStories.hpp
 *
 *  Created on: 1 de mai de 2017
 *      Author: jictyvoo
 */

#include "games/util/os_check_use.h"

void abertura(){
	limpa_tela();
	std::cout << "Jictyvoo apresenta..." << std::endl << "Um super loko RPG" << std::endl;
	std::cout << "\t\t\t\t\t Gonsder RPG!" << std::endl;
	continuar_enter();
}

char inic_menu(){
	char menu_escolha;
	do{
		tecla_buff();
		limpa_tela();
		cout << "1- JOGAR" << endl << "2- COMO JOGAR" << endl << "3- SAIR\n--> ";
		cin >> menu_escolha;
	}while(menu_escolha < '1' || menu_escolha > '3');
	tecla_buff();
	return menu_escolha;
}

void iniciar(){
	limpa_tela();
	cout << "Era uma vez, uma pessoa,\n";
	cout << "que vivia absorta\naté estudar computação,\n";
	cout << "onde seus olhos\nencheram-se de emoção...\n\n";
	cout << "Ela era linda, era bela,\ntão doce e singela\n";
	cout << "mas tão distante ficava\naos desafios que nosso guerreiro enfrentava...\n\n";
	cout << "\nOi, quer jogar?\n";
	continuar_enter();
	limpa_tela();
}
