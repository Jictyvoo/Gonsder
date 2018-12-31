#ifndef COM_BR_HAGENIX_GAMES_MODEL_BACKPACK_H_
#define COM_BR_HAGENIX_GAMES_MODEL_BACKPACK_H_

#include <string>

using namespace std;

class Backpack {
private:
    unsigned short int francis_essence;
    unsigned short int elixir;
    unsigned short int upAtk;
    unsigned short int upDef;
    unsigned short int upAgi;

public:
    Backpack();

    ~Backpack();

    unsigned short int dropItem(unsigned short int chance);

    bool useItem(string nome_item);

    unsigned short int *getStoredItems();

    void setStoredItems(unsigned short int itemsVector[]);

};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_BACKPACK_H_ */
