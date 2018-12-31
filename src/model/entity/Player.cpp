#include <src/controller/Director.h>
#include "Player.h"

Player::Player(string name) {
    this->backpack = new Backpack();

    this->level = 1;
    this->experience = 0;
    this->life = 20 + Director::getInstance()->getRandom(0, 20);
    this->agility = 10 + Director::getInstance()->getRandom(0, 20);
    this->defense = 10 + Director::getInstance()->getRandom(0, 10);
    this->attack = 15 + Director::getInstance()->getRandom(0, 20);
    this->charm = 10 + Director::getInstance()->getRandom(0, 30);
    this->charisma = 20 + Director::getInstance()->getRandom(0, 6);

    this->characterName = std::move(name);

    if (nomainus(this->characterName, "DISNEY", '\0') == 0)
        this->charm = -9990;

    else if ((nomainus(this->characterName, "FRANCIS", '\0') == 0) ||
             (nomainus(this->characterName, "TITO", '\0') == 0))
        this->charm = 9990;

    else if ((nomainus(this->characterName, "JICTYVOO", '\0') == 0) ||
             (nomainus(this->characterName, "JOAO", '\0') == 0)) {
        this->attack = 40;
        this->defense = 30;
    } else if ((nomainus(this->characterName, "ABEL", '\0') == 0) ||
               (nomainus(this->characterName, "HOBBIT", '\0') == 0))
        this->agility = 30;

    else if (nomainus(this->characterName, "VINICIUS", '\0') == 0)
        this->charisma = 500;

    all_regen();
}

Player::Player() {
    this->backpack = new Backpack();
}

Player::~Player() {
    delete this;
    delete this->backpack;
}

bool Player::verifyLevelUp() {
    unsigned long int newLevel;
    unsigned short int temporary = 0;
    do {
        newLevel = this->experience / (100 * (this->level + 1));

        if (newLevel >= this->level) {
            if (newLevel > this->level) {
                this->level = this->level + 1;
                temporary = static_cast<unsigned short>(temporary + 1);
                level_up();
            } else if (newLevel == this->level) {
                return temporary != 0;
            }
        } else
            return false;

    } while (this->level != newLevel);
    return true;
}

void Player::setTotalAttributes(long int *changingArray) {
    this->life = changingArray[0];
    this->agility = changingArray[1];
    this->defense = changingArray[2];
    this->attack = changingArray[3];
    this->charm = changingArray[4];
    this->charisma = changingArray[5];
    this->experience = static_cast<unsigned long>(changingArray[6]);
    this->mana = changingArray[7];
    this->level = static_cast<unsigned long>(changingArray[8]);
}

void Player::setHavingAttributes(string attributeName, long int newValue) {
    if (attributeName == "defense")
        this->defenseHave = newValue;
    else if (attributeName == "agility")
        this->agilityHave = newValue;
    else if (attributeName == "charisma")
        this->charismaHave = newValue;
    else if (attributeName == "attack")
        this->attackHave = newValue;
    else if (attributeName == "life")
        this->lifeHave = newValue;
}

char *Player::getActiveSkill() {
    return this->actives;
}

void Player::setActiveSkill(unsigned short int identifier, char newValue) {
    this->actives[identifier] = newValue;
}

void Player::setSkillChange(string skillName, long int newValue) {
    this->SetMudancaPelasSkills(std::move(skillName), newValue);
}

void Player::resetChangedSkill(string skillName) {
    long int attributesChanged = this->GetMudancaPelasSkills(skillName);
    if (skillName == "inspiration")
        this->charismaHave = this->charismaHave - attributesChanged;
    else if (skillName == "BE_DWARF") {
        this->agilityHave = this->agilityHave - attributesChanged;
        this->attackHave = this->attackHave + attributesChanged;
    } else if (skillName == "BE_GIANT") {
        this->attackHave = this->attackHave - attributesChanged;
        this->agilityHave = this->agilityHave + attributesChanged;
    }
}

void Player::useItem(string changeName, long int change) {
    if (changeName == "Essencia de Francis") {
        if (this->backpack->useItem(changeName)) {
            this->charm = this->charm + change;
            this->charmHave = this->charmHave + change;
        }
    } else if (changeName == "Elixir") {
        if (this->backpack->useItem(changeName))
            this->life_regen();
    } else if (changeName == "Ataque Booster") {
        if (this->backpack->useItem(changeName)) {
            this->attack = this->attack + change;
            this->attackHave = this->attackHave + change;
        }
    } else if (changeName == "Defesa Booster") {
        if (this->backpack->useItem(changeName)) {
            this->defense = this->defense + change;
            this->defenseHave = this->defenseHave + change;
        }
    } else if (changeName == "Agilidade Booster") {
        if (this->backpack->useItem(changeName)) {
            this->agility = this->agility + change;
            this->agilityHave = this->agilityHave + change;
        }
    }
}

unsigned short int Player::levelUpSkill(string skill_selected) {
    if (skill_selected == "inspiration" && (this->skill_points > 0)) {
        this->inspiration = static_cast<unsigned short>(this->inspiration + 1);
        this->skill_points = this->skill_points - 1;
        return this->inspiration;
    } else if (skill_selected == "ABEL'S POWER" && (this->skill_points > 0)) {
        this->BE_DWARF = static_cast<unsigned short>(this->BE_DWARF + 1);
        this->skill_points = this->skill_points - 1;
        return this->BE_DWARF;
    } else if (skill_selected == "AURELIO'S POWER" && (this->skill_points > 0)) {
        this->BE_GIANT = static_cast<unsigned short>(this->BE_GIANT + 1);
        this->skill_points = this->skill_points - 1;
        return this->BE_GIANT;
    } else if (skill_selected == "INVOCAR TRETA" && (this->skill_points > 0)) {
        this->SUMMON_TRETA = static_cast<unsigned short>(this->SUMMON_TRETA + 1);
        this->skill_points = this->skill_points - 1;
        return this->SUMMON_TRETA;
    }
    return 0;
}

bool Player::tryToEscape(unsigned short int chance) {
    if (100000 == chance)
        return false;
    unsigned short int received;
    received = static_cast<unsigned short>(this->level +
                                           (Director::getInstance()->getRandom(0, static_cast<int>(this->agilityHave +
                                                                                                   Director::getInstance()->getRandom(
                                                                                                           0, 5)))));
    return received >= chance;
}

long int Player::winBattle(long int *COMMENEMY, unsigned long int chance, unsigned short int *returnMessages) {
    long int receivedExperience;
    if (COMMENEMY[12] > 2)
        receivedExperience = (COMMENEMY[12] / 2) + Director::getInstance()->getRandom(0,
                                                                                      static_cast<int>(COMMENEMY[12] /
                                                                                                       2));
    else
        receivedExperience = COMMENEMY[12];

    this->experience = this->experience + receivedExperience;

    if (verifyLevelUp())
        returnMessages[0] = 1;
    else
        returnMessages[0] = 0;

    returnMessages[1] = backpack->dropItem(static_cast<unsigned short>(chance));

    return receivedExperience;
}

