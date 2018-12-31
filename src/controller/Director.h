/*
 * Director.h
 *
 *  Created on: 30 de abr de 2017
 *      Author: jictyvoo
 */

#ifndef COM_BR_HAGENIX_GAMES_CONTROLLER_DIRECTOR_H_
#define COM_BR_HAGENIX_GAMES_CONTROLLER_DIRECTOR_H_


/*cpp files to import*/
#include <random>
#include <iostream>
#include <string>

using namespace std;

#include "src/util/os_check_use.h"
#include "src/model/entity/Player.h"
#include "src/model/business/SaveGame.h"

class Director {
private:
    static Director *instance;
    std::random_device random_device; // create object for seeding
    std::mt19937 engine{random_device()}; // create engine and seed it
    Director();

public:
    virtual ~Director();

    int getRandom(int from, int to);

    static Director *getInstance();

    Player *createPlayer(string nome_personagem);

    void showStatus(string nome, long int *vetor, bool main_or_not);

private:
    void auxiliar_companheiros(unsigned short int temporaria, Player *companions[]);

public:
    void apresenta_companheiros(Player *companions[]);

    Player *criar_NALLAS(long int main_status[]);

    Player *criar_enemy_common(long int main_status[]);

    void apresenta_mochila(unsigned short int vetor_itens[]);

    void selecao_mochila(Player **MAIN_PERSONAGEM, string vilao_frases[], short int numero);

private:
    void auxiliar_upaSkill(Player **ESTE_PERSONAGEM, string selecionada);

public:
    bool upa_skill(Player **ESTE_PERSONAGEM);

    unsigned short int
    menu_aventura(string historia_frases, unsigned short int *trecho_historia, Player **MAIN_PERSONAGEM,
                  Player *COMPANHEIROS[]);

    bool save_game(Player **MAIN_CHARACTER, Player *COMPANHEIROS[], unsigned short int *atual_trecho);

    bool load_game(Player **MAIN_CHARACTER, Player *COMPANHEIROS[], unsigned short int *trecho_historia);

};

#endif /* COM_BR_HAGENIX_GAMES_CONTROLLER_DIRECTOR_H_ */
