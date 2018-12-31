/*
 * CombatController.h
 *
 *  Created on: 1 de mai de 2017
 *      Author: jictyvoo
 */

#ifndef COM_BR_HAGENIX_GAMES_CONTROLLER_COMBATCONTROLLER_H_
#define COM_BR_HAGENIX_GAMES_CONTROLLER_COMBATCONTROLLER_H_

#include <string>
#include "Director.h"
#include "util/os_check_use.h"
#include "src/model/entity/Player.h"
#include "src/util/UsableEnums.h"

using namespace std;

class CombatController {
public:
    CombatController();

    virtual ~CombatController();

    unsigned short int acoes_player();

    bool converte_companheiros(Player *COMPANHEIROS[], Player **COMMENEMY);

    bool seduzir_enemy(Player **COMMENEMY, Player *COMPANHEIROS[]);

    bool conversa_diminui(Player **INIMIGO, Player **MAIN_PERSONAGEM, Player *COMPANHEIROS[], string vilao_frases[],
                          unsigned short int numero);

    bool utilizando_auxiliar(unsigned short int indentificacao_skill, Player **MAIN_PERSONAGEM);

    bool utiliza_skills(Player **MAIN_PERSONAGEM);

    bool auxiliar_controle_duracao(Player **ESTE_PERSONAGEM, unsigned short int indentificador, char skills_ativadas[],
                                   string nome_skill);

    void controle_skill_duracao(Player **ESTE_PERSONAGEM);

    void attack_system(Player **INIMIGO, Player **MAIN_PERSONAGEM);

    bool combat_system(Player **MAIN_PERSONAGEM, Player *COMPANHEIROS[], Player **INIMIGO, string vilao_frases[],
                       unsigned short int chance, short int numero);

    bool encontra_inimigos(Player **MAIN_PERSONAGEM, Player *COMPANHEIROS[], Player **INIMIGO,
                           unsigned short int chance_drop, string vilao_frases[],
                           unsigned short int numero_vilao_frases);

};

#endif /* COM_BR_HAGENIX_GAMES_CONTROLLER_COMBATCONTROLLER_H_ */
