/*
 * LiveThing.h
 *
 *  Created on: 30 de abr de 2017
 *      Author: jictyvoo
 */

#ifndef COM_BR_HAGENIX_GAMES_MODEL_LIVETHING_H_
#define COM_BR_HAGENIX_GAMES_MODEL_LIVETHING_H_

#include <string>

using namespace std;

class LiveThing {
public:
    LiveThing();

    virtual ~LiveThing();

protected:
    long int life;
    long int lifeHave;

    long int agility;
    long int agilityHave;

    long int defense;
    long int defenseHave;

    long int attack;
    long int attackHave;

    long int charm;
    long int charmHave;

    long int charisma;
    long int charismaHave;

    unsigned long int experience;
    unsigned long int level;

    string characterName;

protected:
    void level_up();

    void life_regen();

public:

    void all_regen();

    bool setDamage(long int dano);

    string getName();

    void setName(string newName);

    long attackDamage(long *pInt, string basicString, long *pInt1);

    short int criticalHit(string defenderName);

    bool willEvade(long int opponentStrength);

    long int *getCharacterStatus();
};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_LIVETHING_H_ */
