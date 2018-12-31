#ifndef COM_BR_HAGENIX_GAMES_MODEL_CHARACTERSKILL_H_
#define COM_BR_HAGENIX_GAMES_MODEL_CHARACTERSKILL_H_

#include <string>

#include "LiveThing.h"

using namespace std;

class Skills : public LiveThing {
public:
    long int mana;
    long int manaHave;
    unsigned long int skill_points;
    unsigned short int inspiration;    /*Aumenta carisma*/
    unsigned short int SUMMON_TRETA;    /*Invoca uma treta entre os inimigos*/
    unsigned short int BE_DWARF;    /*Diminui ataque, e aumenta agilidade*/
    unsigned short int BE_GIANT;    /*Aumenta ataque, e diminui agilidade*/
    char actives[4];    /*pra verificar quais skills estão ativas*/

private:
    long int inspirationChange;
    long int abelChange;
    long int aurelioChange;
public:
    Skills();

    ~Skills();

    void SetMudancaPelasSkills(string nome_skill, long int newValue);

    long int GetMudancaPelasSkills(string skillName);

    unsigned long int getSkillPoints();

    void addSkillPoints(unsigned long int addedPoints);

    unsigned short int *GetHaveSkills();

    void SetHaveSkills(unsigned short int skills[]);

    unsigned short int *GetTotalHaveMana();

    void SetTotalHaveMana(string have_total, long int newValue);
};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_CHARACTERSKILL_H_ */
