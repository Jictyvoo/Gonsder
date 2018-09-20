#include "Backpack.h"

Backpack::Backpack() {
    this->francis_essence = 0;
    this->elixir = 1;
    this->aumenta_atk = 0;
    this->aumenta_def = 0;
    this->aumenta_agi = 0;
}

Backpack::~Backpack() = default;

unsigned short int Backpack::drop_itens(unsigned short int chance) {
    unsigned short int control;
    control = (unsigned short int) rand() % chance;
    if (control == 0 || (control >= 3 && control <= 5)) {
        this->elixir += 1;
        return 1;
    } else if (control == chance - 1) {
        this->francis_essence += 1;
        return 2;
    } else if (control == 1 || control == chance - 3) {
        this->aumenta_atk += 1;
        return 3;
    } else if (control == 2 || control == chance - 2) {
        this->aumenta_def += 1;
        return 4;
    } else if (control == 6 || control == chance - 7) {
        this->aumenta_agi += 1;
        return 5;
    } else
        return 0;
}

bool Backpack::SetItensQuantity(string nome_item) {
    if (nome_item == "Essencia de Francis" && francis_essence > 0) {
        this->francis_essence -= 1;
        return true;
    }
    if (nome_item == "Elixir" && elixir > 0) {
        this->elixir -= 1;
        return true;
    }
    if (nome_item == "Ataque Booster" && aumenta_atk > 0) {
        this->aumenta_atk -= 1;
        return true;
    }
    if (nome_item == "Defesa Booster" && aumenta_def > 0) {
        this->aumenta_def -= 1;
        return true;
    }
    if (nome_item == "Agilidade Booster" && aumenta_agi > 0) {
        this->aumenta_agi -= 1;
        return true;
    }
    return false;
}

unsigned short int *Backpack::getStoredItems() {
    auto *itemsVector = new unsigned short int[5];
    itemsVector[0] = this->francis_essence;
    itemsVector[1] = this->elixir;
    itemsVector[2] = this->aumenta_atk;
    itemsVector[3] = this->aumenta_def;
    itemsVector[4] = this->aumenta_agi;
    return itemsVector;
}

void Backpack::setStoredItems(unsigned short int itemsVector[]) {
    this->francis_essence = itemsVector[0];
    this->elixir = itemsVector[1];
    this->aumenta_atk = itemsVector[2];
    this->aumenta_def = itemsVector[3];
    this->aumenta_agi = itemsVector[4];
}
