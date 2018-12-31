/*inclusao de bibliotecas*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

#include "util/os_check_use.h"    /*Biblioteca para o uso dos "clearScreen()" , "clearKeyboardBuff()" e "continuar_enter*/
#include "util/name_partner.h"    /*Biblioteca para a verificacao do nome do personagem*/

/*Inclusao de funcoes principais*/

#include "controller/Director.h"
#include "controller/CombatController.h"
#include "StoryScript.hpp"

/*Inicio do programa*/

int main() {
    srand((unsigned) time(nullptr));
    using namespace std;

    /*Instantiating the Director*/
    auto *gameDirector = Director::getInstance();

    Player *companions[4];
    Player *player = nullptr;
    unsigned short int trecho_historia = 1;

    for (unsigned short int temporary = 0; temporary < 4; temporary = static_cast<unsigned short>(temporary + 1))
        companions[temporary] = new Player("");

    char controlVariable = '0';
    StoryScript::getInstance()->opening();
    while (controlVariable != '3') {
        controlVariable = StoryScript::getInstance()->firstMenu();
        if (controlVariable == '1') {

            ifstream save_arquivo;
            save_arquivo.open("savegame.bin", ios::binary);

            if (!save_arquivo.is_open()) {
                do {
                    clearKeyboardBuff();
                    clearScreen();
                    cout << "[1] NEW GAME" << endl << "--> ";
                    cin >> controlVariable;
                } while (controlVariable < '0' || controlVariable > '1');
            } else {
                do {
                    clearKeyboardBuff();
                    clearScreen();
                    cout << "[1] NEW GAME" << endl;
                    cout << "[2] LOAD GAME" << endl << "--> ";
                    cin >> controlVariable;
                } while (controlVariable < '0' || controlVariable > '2');
            }
            clearKeyboardBuff();
            save_arquivo.close();

            if (controlVariable == '1') {
                StoryScript::getInstance()->startText();
                string nome_personagem;
                cout << "Digite o nome do seu personagem\n --> ";
                getline(cin, nome_personagem);
                player = gameDirector->createPlayer(nome_personagem);
                clearKeyboardBuff();
                clearScreen();
                if (!gameDirector->save_game(&player, companions, &trecho_historia))
                    fflush(stdin);
                cout << "Player criado" << endl << "Estatisticas:" << endl << endl;
                gameDirector->showStatus(player->getName(), player->getCharacterStatus(), false);
                continuar_enter();
            } else if (controlVariable == '2') {
                clearScreen();
                player = new Player();
                gameDirector->load_game(&player, companions, &trecho_historia);
                cout << "Dados carregados com success" << endl;
                continuar_enter();
            }
            if (controlVariable != '0') {
                if (trecho_historia == 1)
                    while (gameDirector->menu_aventura(
                            "Em uma pequena vila se encontra\n com doces paisagens a vista...\n", &trecho_historia,
                            &player, companions) != '5');
            }
        } else if (controlVariable == '2') {
            clearScreen();
            cout << "Digite os numeros correspondentes as acoes que deseja tomar" << endl
                 << "escolha suas acoes e acate a zoeira" << endl;
            continuar_enter();
        }
    }

    delete player;
    for (unsigned short int temporary = 0; temporary < 4; temporary = static_cast<unsigned short>(temporary + 1))
        delete companions[temporary];
    return 0;
}
