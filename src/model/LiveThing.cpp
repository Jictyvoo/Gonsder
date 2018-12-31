/*
 * LiveThing.cpp
 *
 *  Created on: 30 de abr de 2017
 *      Author: jictyvoo
 */

#include "LiveThing.h"
#include "src/controller/Director.h"

LiveThing::LiveThing() {

    this->level = 1;
    this->experience = 0;
    this->life = 20 + (Director::getInstance()->getRandom(1, 20) % 20);
    this->agility = 10 + (Director::getInstance()->getRandom(1, 20) % 20);
    this->defense = 10 + (Director::getInstance()->getRandom(1, 10) % 10);
    this->attack = 15 + (Director::getInstance()->getRandom(1, 20) % 20);
    this->charm = 10 + (Director::getInstance()->getRandom(1, 30) % 30);
    this->charisma = 20 + (Director::getInstance()->getRandom(1, 6) % 6);

    this->lifeHave = this->life;
    this->agilityHave = this->agility;
    this->defenseHave = this->defense;
    this->attackHave = this->attack;
    this->charmHave = this->charm;
    this->charismaHave = this->charisma;

}

LiveThing::~LiveThing() = default;

void LiveThing::all_regen() {
    this->lifeHave = this->life;
    this->agilityHave = this->agility;
    this->defenseHave = this->defense;
    this->attackHave = this->attack;
    this->charmHave = this->charm;
    this->charismaHave = this->charisma;
}

void LiveThing::life_regen() {
    this->lifeHave = this->life;
}

bool LiveThing::setDamage(long int dano) {
    if (dano > 0) {
        this->lifeHave = this->lifeHave - dano;
        return true;
    }
    return false;
}

string LiveThing::getName() {
    return this->characterName;
}

void LiveThing::setName(string newName) {
    this->characterName = std::move(newName);
}

long LiveThing::attackDamage(long *pInt, string basicString, long *pInt1) {
    auto damage = static_cast<long>((this->attackHave * 1.15) + (this->agilityHave * 0.50));

    if (damage < 0)
        return 0;

    return damage;
}

short int LiveThing::criticalHit(string defenderName) {
    unsigned int variation;
    unsigned int criticalChance;

    short int criticalPercent;

    variation = static_cast<unsigned int>(defenderName.size());
    criticalChance = (unsigned int) (this->attackHave + this->defenseHave);
    if (criticalChance <= 2)
        return 0;
    if (this->agilityHave > 1)
        criticalChance = (unsigned int) (this->agilityHave * variation) / criticalChance;
    criticalPercent = static_cast<short>(1 + Director::getInstance()->getRandom(1, 50));

    if (criticalChance <= 2)
        return 0;

    long int doCritical;
    doCritical = Director::getInstance()->getRandom(1, (criticalChance * (criticalPercent)));
    if (doCritical <= criticalChance)
        return criticalPercent;
    return 0;
}

bool LiveThing::willEvade(long int opponentStrength) {
    unsigned long int avoidAttack = 0;
    if (this->agilityHave > opponentStrength) {
        avoidAttack = static_cast<unsigned long>(this->agilityHave - opponentStrength);
        while (avoidAttack > 100)
            avoidAttack = avoidAttack / (2 + Director::getInstance()->getRandom(1, 2));

        auto needsToAvoid = static_cast<unsigned long> (Director::getInstance()->getRandom(1, 100));

        return needsToAvoid <= avoidAttack;
    }
    return false;
}

long int *LiveThing::getCharacterStatus() {
    auto *statusVector = new long int[14];
    statusVector[0] = this->life;
    statusVector[1] = this->lifeHave;
    statusVector[2] = this->agility;
    statusVector[3] = this->agilityHave;
    statusVector[4] = this->defense;
    statusVector[5] = this->defenseHave;
    statusVector[6] = this->attack;
    statusVector[7] = this->attackHave;
    statusVector[8] = this->charm;
    statusVector[9] = this->charmHave;
    statusVector[10] = this->charisma;
    statusVector[11] = this->charismaHave;
    statusVector[12] = this->experience;
    statusVector[13] = this->level;
    return statusVector;
}

void LiveThing::level_up() {
    this->life = this->life + Director::getInstance()->getRandom(1, static_cast<int>(10 * this->level));
    this->agility = this->agility + Director::getInstance()->getRandom(1, static_cast<int>(5 * this->level));
    this->defense = this->defense + Director::getInstance()->getRandom(1, static_cast<int>(8 * this->level));
    this->attack = this->attack + Director::getInstance()->getRandom(1, static_cast<int>(9 * this->level));
    this->charm = this->charm + Director::getInstance()->getRandom(1, static_cast<int>(31 * this->level));
    this->charisma = this->charisma + Director::getInstance()->getRandom(1, static_cast<int>(15 * this->level));
    all_regen();
}
