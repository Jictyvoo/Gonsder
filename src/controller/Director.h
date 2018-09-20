/*
 * Director.h
 *
 *  Created on: 30 de abr de 2017
 *      Author: jictyvoo
 */

#ifndef COM_BR_HAGENIX_GAMES_CONTROLLER_DIRECTOR_H_
#define COM_BR_HAGENIX_GAMES_CONTROLLER_DIRECTOR_H_

#include <iostream>
#include <string>

using namespace std;

#include "src/util/os_check_use.h"
#include "src/model/MainCharacter.h"
#include "src/model/SaveGame.h"

class Director {
private:
    static Director *instance;
public:
    Director();

public:
    virtual ~Director();

    static Director *getInstance();

    MainCharacter *criar_personagem_main(string nome_personagem);

    void apresenta_status(string nome, long int vetor[], bool main_or_not);

private:
    void auxiliar_companheiros(unsigned short int temporaria, MainCharacter *COMPANHEIROS[]);

public:
    void apresenta_companheiros(MainCharacter *COMPANHEIROS[]);

    MainCharacter *criar_NALLAS(long int main_status[]);

    MainCharacter *criar_enemy_common(long int main_status[]);

    void apresenta_mochila(unsigned short int vetor_itens[]);

    void selecao_mochila(MainCharacter **MAIN_PERSONAGEM, string vilao_frases[], short int numero);

private:
    void auxiliar_upaSkill(MainCharacter **ESTE_PERSONAGEM, string selecionada);

public:
    bool upa_skill(MainCharacter **ESTE_PERSONAGEM);

    unsigned short int
    menu_aventura(string historia_frases, unsigned short int *trecho_historia, MainCharacter **MAIN_PERSONAGEM,
                  MainCharacter *COMPANHEIROS[]);

    bool save_game(MainCharacter **MAIN_CHARACTER, MainCharacter *COMPANHEIROS[], unsigned short int *atual_trecho);

    bool load_game(MainCharacter **MAIN_CHARACTER, MainCharacter *COMPANHEIROS[], unsigned short int *trecho_historia);

};

#endif /* COM_BR_HAGENIX_GAMES_CONTROLLER_DIRECTOR_H_ */
