/*
 * UserStories.hpp
 *
 *  Created on: 1 de mai de 2017
 *      Author: jictyvoo
 */
#ifndef COM_BR_HAGENIX_GAMES_VIEW_STORYSCRIPT_HPP_
#define COM_BR_HAGENIX_GAMES_VIEW_STORYSCRIPT_HPP_


#include "src/util/os_check_use.h"

class StoryScript {

private:
    static StoryScript *instance;

    StoryScript() {}

public:
    static StoryScript *getInstance() {
        if (instance == nullptr) {
            instance = new StoryScript();
        }
        return instance;
    }

    void opening() {
        clearScreen();
        std::cout << "Jictyvoo apresenta..." << std::endl << "Um super loko RPG" << std::endl;
        std::cout << "\t\t\t\t\t Gonsder RPG!" << std::endl;
        continuar_enter();
    }

    char firstMenu() {
        char menu_escolha;
        do {
            clearKeyboardBuff();
            clearScreen();
            std::cout << "1- JOGAR" << std::endl << "2- COMO JOGAR" << std::endl << "3- SAIR\n--> ";
            std::cin >> menu_escolha;
        } while (menu_escolha < '1' || menu_escolha > '3');
        clearKeyboardBuff();
        return menu_escolha;
    }

    void startText() {
        clearScreen();
        std::cout << "Era uma vez, uma pessoa,\n";
        std::cout << "que vivia absorta\naté estudar computação,\n";
        std::cout << "onde seus olhos\nencheram-se de emoção...\n\n";
        std::cout << "Ela era linda, era bela,\ntão doce e singela\n";
        std::cout << "mas tão distante ficava\naos desafios que nosso guerreiro enfrentava...\n\n";
        std::cout << "\nOi, quer jogar?\n";
        continuar_enter();
        clearScreen();
    }
};

#endif /*COM_BR_HAGENIX_GAMES_VIEW_STORYSCRIPT_HPP_*/
