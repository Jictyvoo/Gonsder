#ifndef COM_BR_HAGENIX_GAMES_MODEL_SAVEGAME_H_
#define COM_BR_HAGENIX_GAMES_MODEL_SAVEGAME_H_

#include "src/model/entity/Player.h"

class SaveGame {

private:
    Player *PRINCIPAL;
private:
    Player *COMPANHEIROS[4];
private:
    unsigned short int trecho_historia;

public:
    SaveGame(Player *MAIN_PERSONAGEM, Player *convertidos[], unsigned short int atual_trecho);

public:
    SaveGame();

public:
    ~SaveGame();

public:
    Player *GetMainCharacterPrincipal();

public:
    void GetCompanheiros(Player *meus_amigos[]);

public:
    unsigned short int GetTrechoHistoria();

};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_SAVEGAME_H_ */
