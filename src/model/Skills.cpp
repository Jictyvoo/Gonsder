#include <src/controller/Director.h>
#include "Skills.h"

Skills::Skills() {
    this->mana = 120 + Director::getInstance()->getRandom(0, 61);
    this->manaHave = this->mana;
    this->skill_points = 0;

    this->inspiration = 0;
    this->SUMMON_TRETA = 0;
    this->BE_DWARF = 0;
    this->BE_GIANT = 0;
    for (char &ativada : actives)
        ativada = false;
    this->aurelioChange = 0;
    this->abelChange = 0;
    this->inspirationChange = 0;
}

Skills::~Skills() = default;

void Skills::SetMudancaPelasSkills(string nome_skill, long int newValue) {
    if (nome_skill == "inspiration")
        this->inspirationChange = newValue;
    else if (nome_skill == "BE_DWARF")
        this->abelChange = newValue;
    else if (nome_skill == "BE_GIANT")
        this->aurelioChange = newValue;
}

long int Skills::GetMudancaPelasSkills(string skillName) {
    if (skillName == "inspiration")
        return this->inspirationChange;
    else if (skillName == "BE_DWARF")
        return this->abelChange;
    else if (skillName == "BE_GIANT")
        return this->aurelioChange;
    return 0;
}

unsigned long int Skills::getSkillPoints() {
    return this->skill_points;
}

void Skills::addSkillPoints(unsigned long int addedPoints) {
    this->skill_points = addedPoints;
}

unsigned short int *Skills::GetHaveSkills() {
    auto *vetor_skills = new unsigned short int[4];
    vetor_skills[0] = this->inspiration;
    vetor_skills[1] = this->SUMMON_TRETA;
    vetor_skills[2] = this->BE_DWARF;
    vetor_skills[3] = this->BE_GIANT;
    return vetor_skills;
}

void Skills::SetHaveSkills(unsigned short int skills[]) {
    this->inspiration = skills[0];
    this->SUMMON_TRETA = skills[1];
    this->BE_DWARF = skills[2];
    this->BE_GIANT = skills[3];
}

unsigned short int *Skills::GetTotalHaveMana() {
    auto *vetor_skills = new unsigned short int[2];
    vetor_skills[0] = static_cast<unsigned short>(this->manaHave);
    vetor_skills[1] = static_cast<unsigned short>(this->mana);
    return vetor_skills;
}

void Skills::SetTotalHaveMana(string have_total, long int newValue) {
    if (have_total == "HAVE")
        this->manaHave = newValue;
    else if (have_total == "TOTAL")
        this->mana = newValue;
}
