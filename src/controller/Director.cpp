/*
 * Director.cpp
 *
 *  Created on: 30 de abr de 2017
 *      Author: jictyvoo
 */

#include "Director.h"

Director::Director() {}

Director::~Director() {}

Director* Director::getInstance(){
	if(instance == nullptr)
			instance = new Director();
	return instance;
}

MainCharacter* Director::criar_personagem_main(string nome_personagem){
	if(nome_personagem.size() > 25){
		char copia[25];
		nome_personagem.copy(copia, 25, 0);
		nome_personagem = copia;
	}
	return new MainCharacter(nome_personagem);
}

void Director::apresenta_status(string nome, long int vetor[], bool main_or_not){
	if(main_or_not == true)
		limpa_tela();
	cout << "VIDA: " << vetor[1] << "/" << vetor[0] << endl;
	cout << "AGILIDADE: " << vetor[3] << "/" << vetor[2] << endl;
	cout << "DEFESA: " << vetor[5] << "/" << vetor[4] << endl;
	cout << "ATAQUE: " << vetor[7] << "/" << vetor[6] << endl;
	cout << "CHARME: " << vetor[9] << "/" << vetor[8] << endl;
	cout << "CARISMA: " << vetor[11] << "/" << vetor[10] << endl;
	cout << "NIVEL: " << vetor[13] << endl;
	cout << "NOME: " << nome << endl;

	if(main_or_not == true){
		char exp_quer;
		tecla_buff();
		cout << "\nPressione ENTER para continuar. . . ";
		exp_quer = getchar();
		if(exp_quer == 'e'){
			limpa_tela();
			cout << "EXPERIENCIA: " << vetor[12] << endl;
			continuar_enter();
		}
		tecla_buff();
	}
}

void Director::auxiliar_companheiros(unsigned short int temporaria, MainCharacter *COMPANHEIROS[]){	/*Auxilia a função "apresenta_companheiros"*/
	limpa_tela();
	cout << COMPANHEIROS[temporaria] -> getName() << " foi embora" << endl;
	COMPANHEIROS[temporaria] -> setName("");
	continuar_enter();
}

void Director::apresenta_companheiros(MainCharacter *COMPANHEIROS[]){

	unsigned short int temporaria = 0;
	unsigned short int controle = 0;

	string nome_personagem[4];
	for(temporaria = 0; temporaria < 4; temporaria = temporaria + 1)
		nome_personagem[temporaria] = COMPANHEIROS[temporaria] -> getName();


	limpa_tela();
	temporaria = 0;
	while(temporaria < 4){
		char letra[] = {'A', 'B', 'C', 'D'};
		if(nome_personagem[temporaria].empty() == false){

			long int *status_companheiro;
			status_companheiro = COMPANHEIROS[temporaria] -> getCharacterStatus();
			cout << (letra[temporaria]) << ")" << endl;
			apresenta_status(nome_personagem[temporaria], status_companheiro, false);
			free(status_companheiro);

			controle = controle + 1;
		}
		temporaria = temporaria + 1;
	}
	if(controle == 0)
		cout << "Ninguem gosta de voce, ta sozinho" << endl;
	char vai_embora;
	tecla_buff();
	printf("\nPressione ENTER para continuar. . . ");
	vai_embora = getchar();

	if((vai_embora == 'a' || vai_embora == 'A') && nome_personagem[0].empty() == false){
		auxiliar_companheiros(0, COMPANHEIROS);
	}
	else if((vai_embora == 'b' || vai_embora == 'B') && nome_personagem[1].empty() == false){
		auxiliar_companheiros(1, COMPANHEIROS);
	}
	else if((vai_embora == 'c' || vai_embora == 'C') && nome_personagem[2].empty() == false){
		auxiliar_companheiros(2, COMPANHEIROS);
	}
	else if((vai_embora == 'd' || vai_embora == 'D') && nome_personagem[3].empty() == false){
		auxiliar_companheiros(3, COMPANHEIROS);
	}
	limpa_tela();
}

MainCharacter* Director::criar_NALLAS(long int main_status[]){
	limpa_tela();
	cout << "NALLAS: Percebi que congelaste com aquela estupefata visao," << endl << "Mas alcanca-la nao ira ";
	cout << "es apenas uma linda ilusao pois minha ela sera" << endl;
	string nallas_frases[8] = {"Voce nunca podera me persuadir\n", "Sempre serei superior a voce\n", "Voce ja perdeu\n", "Voce esta comecando a me animar\n", "Nessa historia eh voce ou eu\n", "A batalha da paixao eh minha\n", "Prepare sua derrota!\n", "Prepare-se para morrer\n"};

	MainCharacter *NALLAS = new MainCharacter("NALLAS");

	long int vetor_status[9];
	vetor_status[0] = 140;
	vetor_status[1] = 35;
	vetor_status[2] = 20;
	vetor_status[3] = 30;
	vetor_status[4] = 400;
	vetor_status[5] = 20;
	vetor_status[6] = 10000;
	vetor_status[7] = ((50 * main_status[13]) + rand() % 25);

	vetor_status[8] = main_status[13];
	NALLAS -> SetTotalAtributos(vetor_status);
	NALLAS -> all_regen();

	return NALLAS;
}

MainCharacter* Director::criar_enemy_common(long int main_status[]){
	string enemy_name[] = {"Kuporig", "Freaky", "Kimataro", "Shagba", "Chimas", "Cielma"};
	MainCharacter *COMMENEMY = new MainCharacter(enemy_name[rand() % 6]);

	long int vetor_status[9];
	vetor_status[0] = ((main_status[0]/2) + rand() % (main_status[0]/2));
	vetor_status[1] = ((main_status[2]/2) + rand() % (main_status[2]/2));
	vetor_status[2] = ((main_status[4]/2) + rand() % (main_status[4]/2));
	vetor_status[3] = ((main_status[6]/2) + rand() % (main_status[6]/2));
	vetor_status[4] = ((main_status[8]/2) + rand() % (main_status[8]/2));
	vetor_status[5] = ((main_status[10]) + rand() % (main_status[10]/2));
	vetor_status[6] = ((25 * main_status[13]) + rand() % 30);
	vetor_status[7] = ((30 * main_status[13]) + rand() % 25);

	vetor_status[8] = main_status[13];
	COMMENEMY -> SetTotalAtributos(vetor_status);
	COMMENEMY -> all_regen();

	string frases_vilao[] = {"Eu vou matar voce!\n", "Suas emocoes sao putridas!\n", "Perceba que suas acoes so pioram tudo!\n", "Por que nao a(o) deixa em paz!?\n", "Porei voce no lugar que merece!\n"};
	cout << frases_vilao[rand() % 5] << endl;

	return COMMENEMY;
}

void Director::apresenta_mochila(unsigned short int vetor_itens[]){
	cout << "Conteudo da Mochila:" << endl;
	if(vetor_itens[0] > 0)
		cout << "1.Essencia de Francis (x " << vetor_itens[0] << ")" << endl;
	if(vetor_itens[1] > 0)
		cout << "2.ELixir (x " << vetor_itens[1] << ")" << endl;
	if(vetor_itens[2] > 0)
		cout << "3.Ataque Booster (x " << vetor_itens[2] << ")" << endl;
	if(vetor_itens[3] > 0)
		cout << "4.Defesa Booster (x " << vetor_itens[3] << ")" << endl;
	if(vetor_itens[4] > 0)
		cout << "5.Agilidade Booster (x " << vetor_itens[4] << ")" << endl;
}

void Director::selecao_mochila(MainCharacter **MAIN_PERSONAGEM, string vilao_frases[], short int numero){

	char escolha;
	unsigned short int *vetor_itens;
	//vetor_itens = (*MAIN_PERSONAGEM) -> GetConteudoMochila();
	do{
		tecla_buff();
		limpa_tela();

		apresenta_mochila(vetor_itens);

		cout << "0.Sair" << endl << " --> ";
		cin >> escolha;
	}while(escolha < '0' || escolha > '5');
	limpa_tela();

	unsigned short int temporaria = 0;
	if(escolha == '1' && vetor_itens[0] > 0){
		unsigned short int mudanca = 10 + rand() % 10;
		(*MAIN_PERSONAGEM) -> Utiliza_itens("Essencia de Francis", mudanca);
		temporaria = 1;
		cout << "Essencia de Francis consumida\t\t +" << mudanca << " em CHARME" << endl;
	}
	else if(escolha == '2' && vetor_itens[1] > 0){
		temporaria = 2;
		(*MAIN_PERSONAGEM) -> Utiliza_itens("Elixir", 0);
		cout << "Vida restaurada!" << endl;
	}
	else if(escolha == '3' && vetor_itens[2] > 0){
		unsigned short int mudanca = 5 + rand() % 5;
		(*MAIN_PERSONAGEM) -> Utiliza_itens("Ataque Booster", mudanca);
		temporaria = 3;
		cout << "Booster de Ataque consumido\t\t +" << mudanca << " em ATAQUE" << endl;
	}
	else if(escolha == '4' && vetor_itens[3] > 0){
		unsigned short int mudanca = 5 + rand() % 5;
		(*MAIN_PERSONAGEM) -> Utiliza_itens("Defesa Booster", mudanca);
		temporaria = 4;
		cout << "Booster de Defesa consumido\t\t +" << mudanca << " em DEFESA" << endl;
	}
	else if(escolha == '5' && vetor_itens[4] > 0){
		unsigned short int mudanca = 5 + rand() % 5;
		(*MAIN_PERSONAGEM) -> Utiliza_itens("Agilidade Booster", mudanca);
		temporaria = 5;
		cout << "Booster de Agilidade consumido\t\t +" << mudanca << " em AGILIDADE" << endl;
	}
	if(temporaria == 0)
		cout << "Sem item requisitado" << endl;
	if(escolha != '0')
		continuar_enter();

	free(vetor_itens);
	tecla_buff();
	limpa_tela();
	cout << vilao_frases[rand() % numero] << endl;
}

void Director::auxiliar_upaSkill(MainCharacter **ESTE_PERSONAGEM, string selecionada){	/*auxilia a função upa_skill*/
	unsigned short int mudanca = (*ESTE_PERSONAGEM) -> UpaSkills(selecionada);
	cout << "O nivel de " << selecionada << " de " << (*ESTE_PERSONAGEM) -> getName() << " subiu para " << mudanca << endl;
}

bool Director::upa_skill(MainCharacter **ESTE_PERSONAGEM){
	if((*ESTE_PERSONAGEM) -> GetSkillPoints() == 0){
		cout << "Pontos de Skill insuficientes!" << endl;
		continuar_enter();
		return false;
	}

	char selecao;
	do{
		limpa_tela();
		tecla_buff();
		unsigned short int *vetor_skills;
		vetor_skills = (*ESTE_PERSONAGEM) -> GetHaveSkills();

		cout << "Voce possui " << (*ESTE_PERSONAGEM) -> GetSkillPoints() << "Pontos de Skill" << endl << endl;
		cout << "Selecione a skill que deseja upar:" << endl;

		cout << "[1] INSPIRACAO (x" << vetor_skills[0] << ")" << endl;
		cout << "[2] INVOCAR TRETA (x" << vetor_skills[1] << ")" << endl;
		cout << "[3] ABEL'S POWER (x" << vetor_skills[2] << ")" << endl;;
		cout << "[4] AURELIO'S POWER (x" << vetor_skills[3] << ")" << endl;;
		cout << "[0] SAIR" << endl << "--> ";

		free(vetor_skills);
		cin >> selecao;
	}while(selecao < '0' || selecao > '4');
	tecla_buff();

	switch(selecao){
		case '1':
			auxiliar_upaSkill(ESTE_PERSONAGEM, "INSPIRACAO");
			break;

		case '2':
			auxiliar_upaSkill(ESTE_PERSONAGEM, "INVOCAR TRETA");
			break;

		case '3':
			auxiliar_upaSkill(ESTE_PERSONAGEM, "ABEL'S POWER");
			break;

		case '4':
			auxiliar_upaSkill(ESTE_PERSONAGEM, "AURELIO'S POWER");
			break;

		case '0':
			return false;
			break;
	}
	continuar_enter();
	if((*ESTE_PERSONAGEM) -> GetSkillPoints() == 0)
		return false;
	return true;
}

unsigned short int Director::menu_aventura(string historia_frases, unsigned short int *trecho_historia, MainCharacter **MAIN_PERSONAGEM, MainCharacter *COMPANHEIROS[]){
	char choices;
	do{
		tecla_buff();
		limpa_tela();
		cout << historia_frases << endl;
		cout << "[1] CONTINUAR HISTORIA" << endl << "[2] TREINAR CONTRA MONSTROS" << endl << "[3] STATUS PERSONAGEM" << endl;
		cout << "[4] DESCANSAR" << endl << "[5] SALVAR E SAIR\n--> " << endl;
		cin >> choices;
	}while(choices < '1' || choices > '5');
	tecla_buff();
	limpa_tela();

	if(choices == '1'){
		long int *status_main;
		status_main = (*MAIN_PERSONAGEM) -> GetStatusMainCharacter();
		MainCharacter *BOSS_NALLAS = criar_NALLAS(status_main);
		free(status_main);

		string vilao_frases[8] = {"Voce nunca podera me persuadir\n", "Sempre serei superior a voce\n", "Voce ja perdeu\n", "Voce esta comecando a me animar\n", "Nessa historia eh voce ou eu\n", "A batalha da paixao eh minha\n", "Prepare sua derrota!\n", "Prepare-se para morrer\n"};
		bool ganha_perde = encontra_inimigos(MAIN_PERSONAGEM, COMPANHEIROS, &BOSS_NALLAS, 10000, vilao_frases, 8);
		if(ganha_perde == false){
			continuar_enter();
			return 5;
		}

		continuar_enter();
	}
	else if(choices == '2'){
		long int *status_main;
		status_main = (*MAIN_PERSONAGEM) -> GetStatusMainCharacter();
		MainCharacter *COMMENEMY_COMMON = criar_enemy_common(status_main);
		free(status_main);

		string frases_vilao[] = {"Eu vou matar voce!\n", "Suas emocoes sao putridas!\n", "Perceba que suas acoes so pioram tudo!\n", "Por que nao a(o) deixa em paz!?\n", "Porei voce no lugar que merece!\n"};
		bool ganha_perde = encontra_inimigos(MAIN_PERSONAGEM, COMPANHEIROS, &COMMENEMY_COMMON, (20 + rand() % 36), frases_vilao, 5);
		if(ganha_perde == false){
			continuar_enter();
			return 5;
		}

		continuar_enter();
	}
	else if(choices == '3'){
		do{
			limpa_tela();
			tecla_buff();
			cout << "[1] VER STATUS" << endl << "[2] VERIFICAR COMPANHEIROS" << endl << "[3] UPDATE SKILLS\n--> " << endl;
			cin >> choices;
		}while(choices < '1' || choices > '3');
		tecla_buff();
		if(choices == '1')
			apresenta_status((*MAIN_PERSONAGEM) -> GetNomeMainCharacter(), (*MAIN_PERSONAGEM) -> GetStatusMainCharacter(), true);
		else if(choices == '2')
			apresenta_companheiros(COMPANHEIROS);
		else
			while(upa_skill(MAIN_PERSONAGEM) != false);
	}

	else if(choices == '4'){
		(*MAIN_PERSONAGEM) -> all_regen();
		cout << "Status retaurados com sucesso" << endl;
		continuar_enter();
	}
	else if(choices == '5'){
		if(save_game(MAIN_PERSONAGEM, COMPANHEIROS, trecho_historia) == true)
			cout << "Game salvo com sucesso" << endl;
		continuar_enter();
	}

	return choices;
}

bool Director::save_game(MainCharacter **MAIN_CHARACTER, MainCharacter *COMPANHEIROS[], unsigned short int *atual_trecho){

	ofstream meu_save;
	meu_save.open("savegame.bin", ios::binary | ios::trunc);

	if(meu_save == NULL){
		cout << "Falha em salvar o game" << endl;
		continuar_enter();
		return false;
	}

	SaveGame *objeto_save = new SaveGame(*MAIN_CHARACTER, COMPANHEIROS, *atual_trecho);
    meu_save.write( (char *)&(*objeto_save), sizeof(SaveGame));
    meu_save.close();

	return true;
}

bool Director::load_game(MainCharacter **MAIN_CHARACTER, MainCharacter *COMPANHEIROS[], unsigned short int *trecho_historia){

	ifstream meu_save;
	meu_save.open("savegame.bin", ios::binary);

	if(meu_save == NULL){
		cout << "Falha em carregar o game" << endl;
		continuar_enter();
		return false;
	}

	SaveGame *objeto_save = new SaveGame();
	meu_save.read( (char *)&(*objeto_save), sizeof(SaveGame));

	(*MAIN_CHARACTER) = objeto_save -> GetMainCharacterPrincipal();

	objeto_save -> GetCompanheiros(COMPANHEIROS);
	meu_save.close();

	return true;
}

