/*inclusao de bibliotecas*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

#include "games/util/os_check_use.h"    /*Biblioteca para o uso dos "limpa_tela()" , "tecla_buff()" e "continuar_enter*/
#include "games/util/padrao_nome.h"    /*Biblioteca para a verificacao do nome do personagem*/

/*INCLUSAO DE CLASSES*/


/*Enumeracoes*/

enum escolhas{atacar, skill_attack, seduzir, mochila, chorar};
enum sucesso{vitoria, derrota, seduzido};

/*Inclusao de funcoes principais*/

#include "games/controller/Director.h"
#include "games/controller/CombatController.h"
#include "UserStories.hpp"

/*Inicio do programa*/

int main(){
	srand( (unsigned)time(NULL) );
	using namespace std;
	
	/*Instanciating the Director*/
	Director* diretorGame = new Director();//Director -> getInstance();

	MainCharacter* COMPANHEIROS[4];
	MainCharacter *MAIN_PERSONAGEM = NULL;
	unsigned short int trecho_historia = 1;

	for(unsigned short int temporaria = 0; temporaria < 4; temporaria = temporaria + 1)
		COMPANHEIROS[temporaria] = new MainCharacter("");
	
	char controle = '0';
	abertura();
	while(controle != '3'){
		controle = diretorGame -> inic_menu();
		if(controle == '1'){
			
			ifstream save_arquivo;
			save_arquivo.open("savegame.bin", ios::binary);
			
			if(save_arquivo == NULL){
				do{
					tecla_buff();
					limpa_tela();
					cout << "[1] NEW GAME" << endl << "--> ";
					cin >> controle;
				}while(controle < '0' || controle > '1');
			}

			else{
				do{
					tecla_buff();
					limpa_tela();
					cout << "[1] NEW GAME" << endl;
					cout << "[2] LOAD GAME" << endl << "--> ";
					cin >> controle;
				}while(controle < '0' || controle > '2');
			}			
			tecla_buff();
			save_arquivo.close();

			if(controle == '1'){
				diretorGame -> iniciar();
				string nome_personagem;
				cout << "Digite o nome do seu personagem\n --> ";
				getline(cin, nome_personagem);
				MAIN_PERSONAGEM = diretorGame -> criar_personagem_main(nome_personagem);
				tecla_buff();
				limpa_tela();
				if(diretorGame -> save_game(&MAIN_PERSONAGEM, COMPANHEIROS, &trecho_historia) == false)
					fflush(stdin);
				cout << "MainCharacter criado" << endl << "Estatisticas:" << endl << endl;
				diretorGame -> apresenta_status(MAIN_PERSONAGEM -> GetNomeMainCharacter(), MAIN_PERSONAGEM -> GetStatusMainCharacter(), false);
				continuar_enter();
			}
			else if(controle == '2'){
				limpa_tela();
				MAIN_PERSONAGEM = new MainCharacter();
				diretorGame -> load_game(&MAIN_PERSONAGEM, COMPANHEIROS, &trecho_historia);
				cout << "Dados carregados com sucesso" << endl;
				continuar_enter();
			}
			if(controle != '0'){
				if(trecho_historia == 1)
					while(diretorGame -> menu_aventura("Em uma pequena vila se encontra\n com doces paisagens a vista...\n", &trecho_historia, &MAIN_PERSONAGEM, COMPANHEIROS) != '5');
			}
		}
		else if(controle == '2'){
			limpa_tela();
			cout << "Digite os numeros correspondentes as acoes que deseja tomar" << endl << "escolha suas acoes e acate a zoeira" << endl;
			continuar_enter();
		}
	}
	
	if(MAIN_PERSONAGEM != NULL)
		delete MAIN_PERSONAGEM;
	for(unsigned short int temporaria = 0; temporaria < 4; temporaria = temporaria + 1)
		delete COMPANHEIROS[temporaria];
	return 0;
}
