#ifndef COM_BR_HAGENIX_GAMES_MODEL_PLAYER_H_
#define COM_BR_HAGENIX_GAMES_MODEL_PLAYER_H_

#include <src/model/LiveThing.h>
#include <src/model/Skills.h>
#include <src/model/Backpack.h>
#include <src/util/name_partner.h>


/*util definitions*/

class Player : public Skills {

private:
    Backpack *backpack;

public:
    explicit Player(string name);

    Player();

    ~Player() override;

private:
    bool verifyLevelUp();

public:
    void setTotalAttributes(long int *changingArray);

    void setHavingAttributes(string attributeName, long int newValue);

    char *getActiveSkill();

    void setActiveSkill(unsigned short int identifier, char newValue);

    void setSkillChange(string skillName, long int newValue);

    void resetChangedSkill(string skillName);

    void useItem(string changeName, long int change);

    unsigned short int levelUpSkill(string skill_selected);

    bool tryToEscape(unsigned short int chance);

    long int winBattle(long int *COMMENEMY, unsigned long int chance, unsigned short int *returnMessages);

};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_PLAYER_H_ */
