#include "SaveGame.h"


SaveGame::SaveGame(Player *MAIN_PERSONAGEM, Player *convertidos[], unsigned short int atual_trecho) {
    this->PRINCIPAL = MAIN_PERSONAGEM;

    for (unsigned short int temporaria = 0; temporaria < 4; temporaria = temporaria + 1)
        this->COMPANHEIROS[temporaria] = convertidos[temporaria];

    this->trecho_historia = atual_trecho;
}

SaveGame::SaveGame() {
    this->PRINCIPAL = new Player();

    for (unsigned short int temporaria = 0; temporaria < 4; temporaria = temporaria + 1)
        this->COMPANHEIROS[temporaria] = new Player();

    this->trecho_historia = 0;
}

SaveGame::~SaveGame() {}

Player *SaveGame::GetMainCharacterPrincipal() {
    return this->PRINCIPAL;
}

void SaveGame::GetCompanheiros(Player *meus_amigos[]) {
    for (unsigned short int temporaria = 0; temporaria < 4; temporaria = temporaria + 1)
        meus_amigos[temporaria] = this->COMPANHEIROS[temporaria];
}

unsigned short int SaveGame::GetTrechoHistoria() {
    return this->trecho_historia;
}
