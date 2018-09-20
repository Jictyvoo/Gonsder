/*
 * CombatController.h
 *
 *  Created on: 1 de mai de 2017
 *      Author: jictyvoo
 */

#ifndef COM_BR_HAGENIX_GAMES_CONTROLLER_COMBATCONTROLLER_H_
#define COM_BR_HAGENIX_GAMES_CONTROLLER_COMBATCONTROLLER_H_

#include <string>
#include "util/os_check_use.h"
#include "model/MainCharacter.h"
using namespace std;

class CombatController {
	public:
		CombatController();
		virtual ~CombatController();

		unsigned short int acoes_player();

		bool converte_companheiros(MainCharacter *COMPANHEIROS[], MainCharacter **COMMENEMY);

		bool seduzir_enemy(MainCharacter **COMMENEMY, MainCharacter *COMPANHEIROS[]);

		bool conversa_diminui(MainCharacter **INIMIGO, MainCharacter **MAIN_PERSONAGEM, MainCharacter *COMPANHEIROS[], string vilao_frases[], unsigned short int numero);

		bool utilizando_auxiliar(unsigned short int indentificacao_skill, MainCharacter **MAIN_PERSONAGEM);

		bool utiliza_skills(MainCharacter **MAIN_PERSONAGEM);

		bool auxiliar_controle_duracao(MainCharacter **ESTE_PERSONAGEM, unsigned short int indentificador, char skills_ativadas[], string nome_skill);

		void controle_skill_duracao(MainCharacter **ESTE_PERSONAGEM);

		void attack_system(MainCharacter **INIMIGO,MainCharacter **MAIN_PERSONAGEM);

		bool combat_system(MainCharacter **MAIN_PERSONAGEM, MainCharacter *COMPANHEIROS[], MainCharacter **INIMIGO, string vilao_frases[], unsigned short int chance, short int numero);

		bool encontra_inimigos(MainCharacter **MAIN_PERSONAGEM, MainCharacter *COMPANHEIROS[], MainCharacter **INIMIGO, unsigned short int chance_drop, string vilao_frases[], unsigned short int numero_vilao_frases);

};

#endif /* COM_BR_HAGENIX_GAMES_CONTROLLER_COMBATCONTROLLER_H_ */
