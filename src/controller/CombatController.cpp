/*
 * CombatController.cpp
 *
 *  Created on: 1 de mai de 2017
 *      Author: jictyvoo
 */

#include "CombatController.h"

CombatController::CombatController() {
    // TODO Auto-generated constructor stub

}

CombatController::~CombatController() {
    // TODO Auto-generated destructor stub
}

unsigned short int CombatController::acoes_player() {
    char escolha;
    unsigned short int controle = 0;
    do {
        if (controle != 0)
            clearScreen();
        cout << "\n [1] ATACAR" << endl << " [2] ESPECIAIS POWERS" << endl << " [3] SEDUZIR" << endl << " [4] MOCHILA"
             << endl << " [5] CHORAR" << endl << "--> ";
        clearKeyboardBuff();
        controle = controle + 1;
        cin >> escolha;
    } while (escolha < '1' || escolha > '5');
    if (escolha == '1')
        return atacar;
    else if (escolha == '2')
        return skill_attack;
    else if (escolha == '3')
        return seduzir;
    else if (escolha == '4')
        return mochila;
    else
        return chorar;
}

bool CombatController::converte_companheiros(Player *COMPANHEIROS[], Player **COMMENEMY) {
    unsigned short int temporaria = 0;
    while (temporaria < 4) {
        if ((COMPANHEIROS[temporaria]->getName()).empty())
            break;
        temporaria = temporaria + 1;
    }
    if (temporaria == 4) {
        cout << "!Incapaz de converter mais inimigos!" << endl;
        continuar_enter();
        clearScreen();
        return false;
    }
    string nome;

    fprintf(stdout, "Nomeei-me meu amigo\n__.> ");
    std::cin >> nome;
    if (nome.size() > 25)
        nome[nome.size() - 1] = '\0';
    (*COMMENEMY)->setName(nome);

    clearScreen();
    clearKeyboardBuff();

    COMPANHEIROS[temporaria] = (*COMMENEMY);
    cout << "Eh uma honra unir-me a voce" << endl;
    return true;
}

bool CombatController::seduzir_enemy(Player **COMMENEMY, Player *COMPANHEIROS[]) {
    clearScreen();
    cout << "Nossa, você realmente é charmoso(a), tens minha atenção" << endl;
    char temporaria = '0';
    do {
        clearKeyboardBuff();
        if (temporaria != '0')
            clearScreen();
        cout << "[1] Dê-me XP para batalhas futuras!" << endl << "[2] Acompanhe-me em minha jornada!" << endl << "--> ";
        cin >> temporaria;
    } while (temporaria < '1' || temporaria > '2');
    clearScreen();
    clearKeyboardBuff();

    bool temporaria_retorno;

    switch (temporaria) {
        case '2':
            converte_companheiros(COMPANHEIROS, COMMENEMY);
            temporaria_retorno = true;
            break;
        case '1':
            temporaria_retorno = false;
            break;
        default:
            break;
    }
    return temporaria_retorno;
}

bool CombatController::conversa_diminui(Player **INIMIGO, Player **MAIN_PERSONAGEM, Player *COMPANHEIROS[],
                                        string vilao_frases[], unsigned short int numero) {
    long int *status_inimigo;
    status_inimigo = (*INIMIGO)->getCharacterStatus();

    string vetor_principal;
    vetor_principal = (*MAIN_PERSONAGEM)->getName();

    if (vetor_principal[9] < status_inimigo[9]) {
        cout << (*INIMIGO)->getName() << " eh charmoso demais para seduzir" << endl;
        free(status_inimigo);

        continuar_enter();
        return false;
    }

    cout << vilao_frases[rand() % numero] << endl;
    unsigned short int mudanca = 1 + (rand() % 3);
    /*1 - Agilidade, 2 - Defesa*/
    switch (mudanca) {
        case 1:
            mudanca = 1 + (rand() % 7);
            status_inimigo[3] = status_inimigo[3] - mudanca;
            (*INIMIGO)->setHavingAttributes("agility", status_inimigo[3]);
            cout << mudanca << " Diminuido da agilidade de " << (*INIMIGO)->getName() << endl;
            break;
        case 2:
            mudanca = 1 + (rand() % 7);
            status_inimigo[5] = status_inimigo[5] - mudanca;
            (*INIMIGO)->setHavingAttributes("defense", status_inimigo[5]);
            cout << mudanca << " Diminuido da defesa de " << (*INIMIGO)->getName() << endl;
            break;
        default:
            cout << (*INIMIGO)->getName() << ": Nunca conseguira me derrotar" << endl;
            break;
    }
    if (status_inimigo[5] <= 0) {
        if (seduzir_enemy(INIMIGO, COMPANHEIROS) == true) {
            free(status_inimigo);
            return true;
        } else {
            free(status_inimigo);
            return true;
        }
    }
    free(status_inimigo);
    return false;
}

bool CombatController::utilizando_auxiliar(unsigned short int indentificacao_skill,
                                           Player **MAIN_PERSONAGEM) {    /*função auxiliar para "utiliza_skills"*/

    unsigned short int *vetor_skills;
    vetor_skills = (*MAIN_PERSONAGEM)->GetHaveSkills();

    unsigned short int *vetor_mana;
    vetor_mana = (*MAIN_PERSONAGEM)->GetTotalHaveMana();

    long int *vetor_atributos;
    vetor_atributos = (*MAIN_PERSONAGEM)->getCharacterStatus();

    long int custo_mana;
    if (indentificacao_skill == 0)
        custo_mana = (30 + (15 * vetor_skills[0]));
    else if (indentificacao_skill == 1)
        custo_mana = (40 + (10 * vetor_skills[1]));
    else if (indentificacao_skill == 2)
        custo_mana = (50 + (10 * vetor_skills[2]));
    else if (indentificacao_skill == 3)
        custo_mana = (50 + (10 * vetor_skills[3]));

    if (vetor_skills[indentificacao_skill] <= 0) {
        cout << "Não Possui Skill selecionada!" << endl;
        free(vetor_skills);
        free(vetor_mana);
        free(vetor_atributos);
        return false;
    } else if (vetor_mana[0] < custo_mana) {
        cout << "Sem mana suficiente!" << endl;
        free(vetor_skills);
        free(vetor_mana);
        free(vetor_atributos);
        return false;
    }

    char *skills_ativadas;
    skills_ativadas = (*MAIN_PERSONAGEM)->getActiveSkill();
    if (skills_ativadas[indentificacao_skill] > 0) {
        cout << "Skill ja ativa!" << endl;
        return false;
    }

    long int mudanca_atributo[4];
    mudanca_atributo[0] = (21 + (rand() % 12)) + ((15 + (rand() % 19)) * (0.15 * vetor_skills[0]));
    mudanca_atributo[1] = (21 + (rand() % 12)) + ((15 + (rand() % 19)) * (0.15 * vetor_skills[1]));
    mudanca_atributo[2] = (17 + (rand() % 22)) + ((17 + (rand() % 22)) * (0.35 * vetor_skills[2]));
    mudanca_atributo[3] = (17 + (rand() % 22)) + ((17 + (rand() % 22)) * (0.35 * vetor_skills[3]));

    string nome_atributo[2];
    string nome_skill;
    unsigned short int qual_atributo[2];
    if (indentificacao_skill == 0) {
        nome_atributo[0] = "charisma";
        nome_atributo[1] = "";
        nome_skill = "inspiration";
        qual_atributo[0] = 11;
        qual_atributo[1] = 0;
    } else if (indentificacao_skill == 1) {
        nome_atributo[0] = "";
        nome_atributo[1] = "";
        nome_skill = "INVOCAR TRETA";
    } else if (indentificacao_skill == 2) {
        nome_atributo[0] = "agility";
        nome_atributo[1] = "attack";
        nome_skill = "ABEL'S POWER";
        qual_atributo[0] = 3;
        qual_atributo[1] = 7;
    } else if (indentificacao_skill == 3) {
        nome_atributo[0] = "attack";
        nome_atributo[1] = "agility";
        nome_skill = "AURELIO'S POWER";
        qual_atributo[0] = 7;
        qual_atributo[1] = 3;
    }

    if (indentificacao_skill == 1)
        return false;

    (*MAIN_PERSONAGEM)->setHavingAttributes(nome_atributo[0], (vetor_atributos[qual_atributo[0]] +
                                                               mudanca_atributo[indentificacao_skill]));
    (*MAIN_PERSONAGEM)->setHavingAttributes(nome_atributo[1], (vetor_atributos[qual_atributo[1]] -
                                                               mudanca_atributo[indentificacao_skill]));

    if (nome_atributo[0].empty() == false)
        cout << nome_atributo[0] << " aumentado(a) em " << mudanca_atributo[indentificacao_skill];
    if (nome_atributo[1].empty() == false)
        cout << "e " << nome_atributo[1] << " diminuido(a) em " << mudanca_atributo[indentificacao_skill];
    cout << endl;

    char tempo_duracao = (char) (5 + vetor_skills[indentificacao_skill]) / 3;
    (*MAIN_PERSONAGEM)->SetTotalHaveMana("HAVE", custo_mana);
    (*MAIN_PERSONAGEM)->setActiveSkill(indentificacao_skill, tempo_duracao);

    free(vetor_skills);
    free(vetor_mana);
    free(vetor_atributos);
    return true;
}

bool CombatController::utiliza_skills(Player **MAIN_PERSONAGEM) {
    char escolha;
    do {
        clearKeyboardBuff();
        clearScreen();

        unsigned short int *vetor_skills;
        vetor_skills = (*MAIN_PERSONAGEM)->GetHaveSkills();

        if (vetor_skills[0] > 0)
            cout << "[1] inspiration (" << (30 + (15 * vetor_skills[0])) << ")" << endl;
        if (vetor_skills[1] > 0)
            cout << "[2] INVOCAR TRETA (" << (40 + (10 * vetor_skills[1])) << ")" << endl;
        if (vetor_skills[2] > 0)
            cout << "[3] ABEL' POWER (" << (50 + (10 * vetor_skills[2])) << ")" << endl;
        if (vetor_skills[3] > 0)
            cout << "[4] AURELIO'S POWER (" << (50 + (10 * vetor_skills[3])) << ")" << endl;
        cout << "[0] SAIR" << endl;
        free(vetor_skills);

        unsigned short int *vetor_mana;
        vetor_mana = (*MAIN_PERSONAGEM)->GetTotalHaveMana();
        cout << "MANA: " << vetor_mana[0] << "/" << vetor_mana[1] << endl << "--> ";
        free(vetor_mana);

        cin >> escolha;
    } while (escolha < '0' || escolha > '4');
    clearKeyboardBuff();

    switch (escolha) {
        case '0':
            cout << "Nenhuma Skill utilizada!" << endl;
            break;

        case '1':
            utilizando_auxiliar(0, MAIN_PERSONAGEM);
            break;

        case '2':
            utilizando_auxiliar(1, MAIN_PERSONAGEM);
            break;

        case '3':
            utilizando_auxiliar(2, MAIN_PERSONAGEM);
            break;

        case '4':
            utilizando_auxiliar(3, MAIN_PERSONAGEM);
            break;
    }
    return true;
}

bool CombatController::auxiliar_controle_duracao(Player **ESTE_PERSONAGEM, unsigned short int indentificador,
                                                 char skills_ativadas[],
                                                 string nome_skill) {    /*auxilia controle_skill_duracao*/
    if (skills_ativadas[indentificador] > 0) {
        skills_ativadas[indentificador] = skills_ativadas[indentificador] - 1;
        if (skills_ativadas[indentificador] != 0)
            cout << nome_skill << " permanecera ativa por mais " << skills_ativadas[indentificador] << " turnos"
                 << endl;
        else if (skills_ativadas[indentificador] == 0) {
            if (indentificador != 1)
                (*ESTE_PERSONAGEM)->resetChangedSkill(nome_skill);
            cout << nome_skill << " perdeu o efeito" << endl;
            return false;
        }
        return true;
    }
    return false;
}

void CombatController::controle_skill_duracao(Player **ESTE_PERSONAGEM) {
    /*retorna 0 se não perdeu efeito, 1 se a primeira skill perdeu efeito e assim por diante*/
    char *skills_ativadas;
    skills_ativadas = (*ESTE_PERSONAGEM)->getActiveSkill();

    auxiliar_controle_duracao(ESTE_PERSONAGEM, 0, skills_ativadas, "inspiration");
    auxiliar_controle_duracao(ESTE_PERSONAGEM, 1, skills_ativadas, "SUMMON_TRETA");
    auxiliar_controle_duracao(ESTE_PERSONAGEM, 2, skills_ativadas, "BE_DWARF");
    auxiliar_controle_duracao(ESTE_PERSONAGEM, 3, skills_ativadas, "BE_GIANT");
}

void CombatController::attack_system(Player **INIMIGO, Player **MAIN_PERSONAGEM) {
    long int auxiliar;
    long int temporaria;
    bool evadiu;

    long int taxa_critico;
    long int *dados_atributos;

    /*PRIMEIRO attack DO ALIADO*/
    dados_atributos = (*INIMIGO)->getCharacterStatus();
    auxiliar = (*MAIN_PERSONAGEM)->attackDamage(dados_atributos, (*INIMIGO)->getName(), &taxa_critico);
    free(dados_atributos);

    if (auxiliar > 1) { temporaria = (auxiliar / 2) + (rand() % (auxiliar / 2)); }
    else { temporaria = auxiliar; }

    dados_atributos = (*MAIN_PERSONAGEM)->getCharacterStatus();
    if (temporaria > 0)
        evadiu = (*INIMIGO)->willEvade(reinterpret_cast<long>(dados_atributos));
    free(dados_atributos);

    if (evadiu != true) {
        (*INIMIGO)->setDamage(temporaria);
        cout << (*MAIN_PERSONAGEM)->getName() << " infringiu " << temporaria << " de Dano" << endl;
    } else
        cout << (*INIMIGO)->getName() << " evadiu o golpe" << endl;

    /*SEGUNDO attack DO INIMIGO*/
    dados_atributos = (*MAIN_PERSONAGEM)->getCharacterStatus();
    auxiliar = (*INIMIGO)->attackDamage(dados_atributos, (*MAIN_PERSONAGEM)->getName(), &taxa_critico);
    free(dados_atributos);

    if (auxiliar > 1) { temporaria = (auxiliar / 2) + (rand() % (auxiliar / 2)); }
    else { temporaria = auxiliar; }

    dados_atributos = (*INIMIGO)->getCharacterStatus();
    if (temporaria > 0)
        evadiu = (*MAIN_PERSONAGEM)->willEvade(reinterpret_cast<long>(dados_atributos));
    free(dados_atributos);

    if (evadiu != true) {
        (*MAIN_PERSONAGEM)->setDamage(temporaria);
        cout << (*INIMIGO)->getName() << " infringiu " << temporaria << " de Dano" << endl;
    } else
        cout << (*MAIN_PERSONAGEM)->getName() << " evadiu o golpe" << endl;
}

bool CombatController::combat_system(Player **MAIN_PERSONAGEM, Player *COMPANHEIROS[], Player **INIMIGO,
                                     string vilao_frases[], unsigned short int chance, short int numero) {
    unsigned short int escolha;

    long int *vetor_status_main;
    vetor_status_main = (*MAIN_PERSONAGEM)->getCharacterStatus();

    long int *vetor_status_enemy;
    vetor_status_enemy = (*INIMIGO)->getCharacterStatus();
    do {

        controle_skill_duracao(MAIN_PERSONAGEM);

        escolha = acoes_player();
        clearScreen();
        switch (escolha) {
            case atacar:
                attack_system(INIMIGO, MAIN_PERSONAGEM);
                cout << vilao_frases[rand() % numero] << endl << endl;

                free(vetor_status_main);
                free(vetor_status_enemy);
                vetor_status_main = (*MAIN_PERSONAGEM)->getCharacterStatus();
                vetor_status_enemy = (*INIMIGO)->getCharacterStatus();

                cout << (*MAIN_PERSONAGEM)->getName() << " LIFE: " << vetor_status_main[1] << "/"
                     << vetor_status_main[0] << endl;
                cout << (*INIMIGO)->getName() << " LIFE: " << vetor_status_enemy[1] << "/"
                     << vetor_status_enemy[0] << endl;
                if (vetor_status_main[1] <= 0) {
                    cout << "GAME OVER" << endl;
                    free(vetor_status_main);
                    free(vetor_status_enemy);
                    return false;
                }
                break;

            case skill_attack:
                utiliza_skills(MAIN_PERSONAGEM);
                continuar_enter();
                clearScreen();
                break;

            case seduzir:
                if (conversa_diminui(INIMIGO, MAIN_PERSONAGEM, COMPANHEIROS, vilao_frases, numero))
                    /*(*INIMIGO) -> setHavingAttributes("life", 0);*/vetor_status_enemy[1] = 0;

                break;

            case mochila:
                Director::getInstance()->selecao_mochila(MAIN_PERSONAGEM, vilao_frases, numero);
                break;

            case chorar:
                if (!(*MAIN_PERSONAGEM)->tryToEscape(chance)) {
                    cout << "Vergonha pra voce, pro seu cachorro, e pra sua PAIXAO!" << endl;
                    return false;
                } else
                    cout << vilao_frases[rand() % numero] << endl;
                break;
        }

    } while (vetor_status_enemy[1] > 0 && vetor_status_main[1] > 0);

    if (vetor_status_enemy[1] <= 0) {
        free(vetor_status_main);
        free(vetor_status_enemy);
        return true;
    } else if (vetor_status_main[1] <= 0) {
        free(vetor_status_main);
        free(vetor_status_enemy);
        return false;
    }
    free(vetor_status_main);
    free(vetor_status_enemy);
    return true;
}

bool CombatController::encontra_inimigos(Player **MAIN_PERSONAGEM, Player *COMPANHEIROS[], Player **INIMIGO,
                                         unsigned short int chance_drop, string vilao_frases[],
                                         unsigned short int numero_vilao_frases) {
    unsigned short int mensagens_retorno[2];

    string vetor_nome_itens[] = {"Elixir", "Essencia de Francis", "Ataque Booster", "Defesa Boster",
                                 "Agilidade Booster"};

    long int *status_inimigo;
    status_inimigo = (*INIMIGO)->getCharacterStatus();

    if (combat_system(MAIN_PERSONAGEM, COMPANHEIROS, INIMIGO, vilao_frases, chance_drop, numero_vilao_frases) == true) {

        long int experiencia_ganha = (*MAIN_PERSONAGEM)->winBattle(status_inimigo, chance_drop, mensagens_retorno);

        long int *status_personagem;
        status_personagem = (*MAIN_PERSONAGEM)->getCharacterStatus();

        cout << endl << (*MAIN_PERSONAGEM)->getName() << " recebeu " << experiencia_ganha << " de experiencia" << endl;

        if (mensagens_retorno[0] == 1)
            cout << (*MAIN_PERSONAGEM)->getName() << " upou para o nivel: " << status_personagem[13] << endl;

        if (mensagens_retorno[1] > 0)
            cout << (*INIMIGO)->getName() << " dropou " << vetor_nome_itens[mensagens_retorno[1] - 1] << endl;
        else
            cout << (*INIMIGO)->getName() << " era universitario, sem itens" << endl;

        free(status_personagem);
        free(status_inimigo);
        return vitoria;
    } else {
        free(status_inimigo);
        return derrota;
    }
}
