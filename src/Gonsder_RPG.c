#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dina_string.h"    /*Biblioteca criada por João Victor Oliveira Couto*/
#include "padrao_nome.h"    /*Biblioteca criada por João Victor Oliveira Couto*/
#include "os_check_use.h"    /*Biblioteca criada por João Victor Oliveira Couto*/

enum escolhas {
    atacar, skill_attack, conversar, mochila, chorar
};
enum sucesso {
    vitoria, derrota, seduzido
};
enum leveis_sobe {
    upa_nivel, same_nivel
};

typedef struct status_player {
    long int VIDA;
    long int AGILIDADE;
    long int DEFESA;
    long int ATAQUE;
    long int CHARME;
    long int CARISMA;
    unsigned long int EXPERIENCIA;
    unsigned long int NIVEL;
    char *NOME_PERSONAGEM;
} atributos;

typedef struct conteudo_mochila {
    unsigned short int francis_essence;
    unsigned short int elixir;
    unsigned short int aumenta_atk;
    unsigned short int aumenta_def;
    unsigned short int aumenta_agi;
} mochilinha;

typedef struct status_have {
    long int have_life;
    long int have_agility;
    long int have_defense;
    long int have_attack;
    long int have_luck;
    long int have_charism;
} tem_status;

typedef struct utiliza_skill {
    long int TOTAL_MANA;
    long int have_mana;
    unsigned long int skill_points;
    unsigned short int INSPIRACAO;    /*Aumenta carisma*/
    unsigned short int SUMMON_TRETA;    /*Invoca uma treta entre os inimigos*/
    unsigned short int BE_DWARF;    /*Diminui ataque, e aumenta agilidade*/
    unsigned short int BE_GIANT;    /*Aumenta ataque, e diminui agilidade*/
} the_skills;

typedef struct lista_friends {
    tem_status THEY_HAVE[4];
    atributos THEY_TOTAL[4];
    unsigned short int existentes[4];
} status_friends;

atributos MAIN_CHARACTER;
mochilinha MAIN_PERSONAGEM;
tem_status HAVE_CHARACTER;
the_skills SKILL_CHARACTER;
long int dados_save[27];

void continuar_enter(void) {    /*função para reset das informações exibidas e continuação da execução do programa*/
    tecla_buff();
    printf("\nPressione ENTER para continuar. . . ");
    getchar();
    tecla_buff();
}

void abertura() {
    limpa_tela();
    printf("Jictyvoo apresenta...\nUm super loko RPG\n");
    printf("\t\t\t\t\t Gonsder RPG!\n");
    continuar_enter();
}

unsigned short int save_game(status_friends *COMPANHEIROS) {
    dados_save[0] = MAIN_CHARACTER.VIDA;
    dados_save[1] = MAIN_CHARACTER.AGILIDADE;
    dados_save[2] = MAIN_CHARACTER.DEFESA;
    dados_save[3] = MAIN_CHARACTER.NIVEL;
    dados_save[4] = MAIN_CHARACTER.ATAQUE;
    dados_save[5] = MAIN_CHARACTER.CHARME;
    dados_save[6] = MAIN_CHARACTER.CARISMA;
    dados_save[7] = MAIN_CHARACTER.EXPERIENCIA;
    dados_save[8] = SKILL_CHARACTER.TOTAL_MANA;

    dados_save[9] = HAVE_CHARACTER.have_life;
    dados_save[10] = HAVE_CHARACTER.have_agility;
    dados_save[11] = HAVE_CHARACTER.have_defense;
    dados_save[12] = HAVE_CHARACTER.have_attack;
    dados_save[13] = HAVE_CHARACTER.have_luck;
    dados_save[14] = HAVE_CHARACTER.have_charism;
    dados_save[15] = SKILL_CHARACTER.have_mana;
    dados_save[16] = SKILL_CHARACTER.skill_points;

    dados_save[17] = SKILL_CHARACTER.INSPIRACAO;
    dados_save[18] = SKILL_CHARACTER.SUMMON_TRETA;
    dados_save[19] = SKILL_CHARACTER.BE_DWARF;
    dados_save[20] = SKILL_CHARACTER.BE_GIANT;

    dados_save[21] = MAIN_PERSONAGEM.francis_essence;
    dados_save[22] = MAIN_PERSONAGEM.elixir;
    dados_save[23] = MAIN_PERSONAGEM.aumenta_atk;
    dados_save[24] = MAIN_PERSONAGEM.aumenta_def;
    dados_save[25] = MAIN_PERSONAGEM.aumenta_agi;

    FILE *meu_salve;
    meu_salve = fopen("savegame.bin", "wb");
    if (meu_salve == NULL) {
        fprintf(stdout, "Falha em salvar o game\n");
        continuar_enter();
        return derrota;
    }
    fwrite(dados_save, sizeof(long int), 27, meu_salve);
    fwrite(MAIN_CHARACTER.NOME_PERSONAGEM, sizeof(char), 25, meu_salve);

    unsigned short int temporaria = 0;
    long int companions[14];
    char *names_friends;

    while (temporaria < 4) {
        companions[0] = COMPANHEIROS->THEY_TOTAL[temporaria].VIDA;
        companions[1] = COMPANHEIROS->THEY_TOTAL[temporaria].AGILIDADE;
        companions[2] = COMPANHEIROS->THEY_TOTAL[temporaria].DEFESA;
        companions[3] = COMPANHEIROS->THEY_TOTAL[temporaria].NIVEL;
        companions[4] = COMPANHEIROS->THEY_TOTAL[temporaria].ATAQUE;
        companions[5] = COMPANHEIROS->THEY_TOTAL[temporaria].CHARME;
        companions[6] = COMPANHEIROS->THEY_TOTAL[temporaria].CARISMA;
        companions[7] = COMPANHEIROS->THEY_TOTAL[temporaria].EXPERIENCIA;

        companions[8] = COMPANHEIROS->THEY_HAVE[temporaria].have_life;
        companions[9] = COMPANHEIROS->THEY_HAVE[temporaria].have_agility;
        companions[10] = COMPANHEIROS->THEY_HAVE[temporaria].have_defense;
        companions[11] = COMPANHEIROS->THEY_HAVE[temporaria].have_attack;
        companions[12] = COMPANHEIROS->THEY_HAVE[temporaria].have_luck;
        companions[13] = COMPANHEIROS->THEY_HAVE[temporaria].have_charism;

        names_friends = COMPANHEIROS->THEY_TOTAL[temporaria].NOME_PERSONAGEM;

        fwrite(companions, sizeof(long int), 14, meu_salve);
        fwrite(names_friends, sizeof(char), 25, meu_salve);
        temporaria += 1;
    }
    fwrite(COMPANHEIROS->existentes, sizeof(unsigned short int), 4, meu_salve);

    fclose(meu_salve);
    return vitoria;
}

unsigned short int load_game(status_friends *COMPANHEIROS) {
    FILE *meu_salve;
    meu_salve = fopen("savegame.bin", "rb");
    if (meu_salve == NULL) {
        return derrota;
    } else {
        fread(dados_save, sizeof(long int), 27, meu_salve);
        MAIN_CHARACTER.VIDA = dados_save[0];
        MAIN_CHARACTER.AGILIDADE = dados_save[1];
        MAIN_CHARACTER.DEFESA = dados_save[2];
        MAIN_CHARACTER.NIVEL = dados_save[3];
        MAIN_CHARACTER.ATAQUE = dados_save[4];
        MAIN_CHARACTER.CHARME = dados_save[5];
        MAIN_CHARACTER.CARISMA = dados_save[6];
        MAIN_CHARACTER.EXPERIENCIA = dados_save[7];
        SKILL_CHARACTER.TOTAL_MANA = dados_save[8];

        HAVE_CHARACTER.have_life = dados_save[9];
        HAVE_CHARACTER.have_agility = dados_save[10];
        HAVE_CHARACTER.have_defense = dados_save[11];
        HAVE_CHARACTER.have_attack = dados_save[12];
        HAVE_CHARACTER.have_luck = dados_save[13];
        HAVE_CHARACTER.have_charism = dados_save[14];
        SKILL_CHARACTER.have_mana = dados_save[15];
        SKILL_CHARACTER.skill_points = dados_save[16];

        SKILL_CHARACTER.INSPIRACAO = dados_save[17];
        SKILL_CHARACTER.SUMMON_TRETA = dados_save[18];
        SKILL_CHARACTER.BE_DWARF = dados_save[19];
        SKILL_CHARACTER.BE_GIANT = dados_save[20];

        MAIN_PERSONAGEM.francis_essence = dados_save[21];
        MAIN_PERSONAGEM.elixir = dados_save[22];
        MAIN_PERSONAGEM.aumenta_atk = dados_save[23];
        MAIN_PERSONAGEM.aumenta_def = dados_save[24];
        MAIN_PERSONAGEM.aumenta_agi = dados_save[25];

        char *nome_personagem = (char *) malloc(25 * sizeof(char));
        fread(nome_personagem, sizeof(char), 25, meu_salve);
        MAIN_CHARACTER.NOME_PERSONAGEM = nome_personagem;

        unsigned short int temporaria = 0;
        unsigned long int companions[14];
        char *names_friends;

        while (temporaria < 4) {
            fread(companions, sizeof(long int), 14, meu_salve);
            names_friends = (char *) calloc(25, sizeof(char));
            fread(names_friends, sizeof(char), 25, meu_salve);

            COMPANHEIROS->THEY_TOTAL[temporaria].NOME_PERSONAGEM = names_friends;

            COMPANHEIROS->THEY_TOTAL[temporaria].VIDA = companions[0];
            COMPANHEIROS->THEY_TOTAL[temporaria].AGILIDADE = companions[1];
            COMPANHEIROS->THEY_TOTAL[temporaria].DEFESA = companions[2];
            COMPANHEIROS->THEY_TOTAL[temporaria].NIVEL = companions[3];
            COMPANHEIROS->THEY_TOTAL[temporaria].ATAQUE = companions[4];
            COMPANHEIROS->THEY_TOTAL[temporaria].CHARME = companions[5];
            COMPANHEIROS->THEY_TOTAL[temporaria].CARISMA = companions[6];
            COMPANHEIROS->THEY_TOTAL[temporaria].EXPERIENCIA = companions[7];

            COMPANHEIROS->THEY_HAVE[temporaria].have_life = companions[8];
            COMPANHEIROS->THEY_HAVE[temporaria].have_agility = companions[9];
            COMPANHEIROS->THEY_HAVE[temporaria].have_defense = companions[10];
            COMPANHEIROS->THEY_HAVE[temporaria].have_attack = companions[11];
            COMPANHEIROS->THEY_HAVE[temporaria].have_luck = companions[12];
            COMPANHEIROS->THEY_HAVE[temporaria].have_charism = companions[13];

            temporaria += 1;
        }
        fread(COMPANHEIROS->existentes, sizeof(unsigned short int), 4, meu_salve);

        fclose(meu_salve);
        return vitoria;
    }
}

unsigned short int upa_skill(the_skills *SKILL_PERSONAGEM, atributos MAIN_PERSONAGEM) {
    if (SKILL_PERSONAGEM->skill_points == 0) {
        fprintf(stdout, "Pontos de Skill insuficientes!\n");
        continuar_enter();
        return derrota;
    }
    unsigned short int selecao;
    do {
        limpa_tela();
        tecla_buff();
        fprintf(stdout, "Voce possui %ld Pontos de Skill\n\n", (*SKILL_PERSONAGEM).skill_points);
        fprintf(stdout, "Selecione a skill que deseja upar:\n");
        fprintf(stdout, "[1] INSPIRACAO (x%hu)\n", SKILL_PERSONAGEM->INSPIRACAO);
        fprintf(stdout, "[2] INVOCAR TRETA (x%hu)\n", SKILL_PERSONAGEM->SUMMON_TRETA);
        fprintf(stdout, "[3] ABEL'S POWER (x%hu)\n", SKILL_PERSONAGEM->BE_DWARF);
        fprintf(stdout, "[4] AURELIO'S POWER (x%hu)\n", SKILL_PERSONAGEM->BE_GIANT);
        fprintf(stdout, "[0] SAIR\n--> ");
    } while (!fscanf(stdin, "%hu", &selecao) || selecao < 0 || selecao > 4);
    tecla_buff();
    switch (selecao) {
        case 1:
            SKILL_PERSONAGEM->INSPIRACAO = SKILL_PERSONAGEM->INSPIRACAO + 1;
            SKILL_PERSONAGEM->skill_points = SKILL_PERSONAGEM->skill_points - 1;
            fprintf(stdout, "O nivel de INSPIRACAO de %s subiu para %hu\n", MAIN_PERSONAGEM.NOME_PERSONAGEM,
                    SKILL_PERSONAGEM->INSPIRACAO);
            break;

        case 2:
            SKILL_PERSONAGEM->SUMMON_TRETA = SKILL_PERSONAGEM->SUMMON_TRETA + 1;
            SKILL_PERSONAGEM->skill_points = SKILL_PERSONAGEM->skill_points - 1;
            fprintf(stdout, "O nivel de INVOCAR TRETA de %s subiu para %hu\n", MAIN_PERSONAGEM.NOME_PERSONAGEM,
                    SKILL_PERSONAGEM->SUMMON_TRETA);
            break;

        case 3:
            SKILL_PERSONAGEM->BE_DWARF = SKILL_PERSONAGEM->BE_DWARF + 1;
            SKILL_PERSONAGEM->skill_points = SKILL_PERSONAGEM->skill_points - 1;
            fprintf(stdout, "O nivel de ABEL'S POWER de %s subiu para %hu\n", MAIN_PERSONAGEM.NOME_PERSONAGEM,
                    SKILL_PERSONAGEM->BE_DWARF);
            break;

        case 4:
            SKILL_PERSONAGEM->BE_GIANT = SKILL_PERSONAGEM->BE_GIANT + 1;
            SKILL_PERSONAGEM->skill_points = SKILL_PERSONAGEM->skill_points - 1;
            fprintf(stdout, "O nivel de AURELIO'S POWER de %s subiu para %hu\n", MAIN_PERSONAGEM.NOME_PERSONAGEM,
                    SKILL_PERSONAGEM->BE_GIANT);
            break;
        case 0:
            return derrota;
            break;
        default:
            break;
    }
    continuar_enter();
    if (SKILL_PERSONAGEM->skill_points == 0)
        return derrota;
    return vitoria;
}

void status_regen(atributos *TOTAL, tem_status *I_HAVE, the_skills *SKILL_PERSONAGEM) {
    (*I_HAVE).have_life = (*TOTAL).VIDA;
    (*I_HAVE).have_agility = (*TOTAL).AGILIDADE;
    (*I_HAVE).have_defense = (*TOTAL).DEFESA;
    (*I_HAVE).have_attack = (*TOTAL).ATAQUE;
    (*I_HAVE).have_luck = (*TOTAL).CHARME;
    (*I_HAVE).have_charism = (*TOTAL).CARISMA;
    SKILL_PERSONAGEM->have_mana = SKILL_PERSONAGEM->TOTAL_MANA;
}

void level_up() {
    MAIN_CHARACTER.VIDA = MAIN_CHARACTER.VIDA + (rand() % (10 * MAIN_CHARACTER.NIVEL));
    MAIN_CHARACTER.AGILIDADE = MAIN_CHARACTER.AGILIDADE + (rand() % (5 * MAIN_CHARACTER.NIVEL));
    MAIN_CHARACTER.DEFESA = MAIN_CHARACTER.DEFESA + (rand() % (8 * MAIN_CHARACTER.NIVEL));
    MAIN_CHARACTER.ATAQUE = MAIN_CHARACTER.ATAQUE + (rand() % (9 * MAIN_CHARACTER.NIVEL));
    MAIN_CHARACTER.CHARME = MAIN_CHARACTER.CHARME + (rand() % (31 * MAIN_CHARACTER.NIVEL));
    MAIN_CHARACTER.CARISMA = MAIN_CHARACTER.CARISMA + (rand() % (15 * MAIN_CHARACTER.NIVEL));
    SKILL_CHARACTER.TOTAL_MANA = (long int) SKILL_CHARACTER.TOTAL_MANA +
                                 (rand() % (15 + (MAIN_CHARACTER.EXPERIENCIA / (100 * (MAIN_CHARACTER.NIVEL + 1)))));

    SKILL_CHARACTER.have_mana = SKILL_CHARACTER.TOTAL_MANA;
    SKILL_CHARACTER.skill_points = SKILL_CHARACTER.skill_points + 1;
    status_regen(&MAIN_CHARACTER, &HAVE_CHARACTER, &SKILL_CHARACTER);
}

unsigned short int verifica_upa(atributos *MAIN_PERSONAGEM) {
    unsigned long int novo_nivel;
    unsigned short int temporaria = 0;
    do {
        novo_nivel = (unsigned long int) MAIN_PERSONAGEM->EXPERIENCIA / (100 * (MAIN_PERSONAGEM->NIVEL + 1));

        if (novo_nivel >= MAIN_PERSONAGEM->NIVEL) {
            if (novo_nivel > MAIN_PERSONAGEM->NIVEL) {
                MAIN_PERSONAGEM->NIVEL = (unsigned long int) MAIN_PERSONAGEM->NIVEL + 1;
                temporaria = temporaria + 1;
                level_up();
            } else if (novo_nivel == MAIN_PERSONAGEM->NIVEL) {
                if (temporaria != 0)
                    return upa_nivel;
                return same_nivel;
            }
        } else
            return same_nivel;

    } while (MAIN_PERSONAGEM->NIVEL != novo_nivel);
    return upa_nivel;
}

void nome_player(status_friends *COMPANHEIROS) {
    char *nome_personagem;
    fprintf(stdout, "Digite o nome do seu personagem\n --> ");
    fdina_scan(stdin, &nome_personagem, '\n');
    if (strlen(nome_personagem) > 25)
        nome_personagem[25] = '\0';
    tecla_buff();
    limpa_tela();

    unsigned short int temporaria = 0;
    while (temporaria < 4) {
        COMPANHEIROS->existentes[temporaria] = derrota;
        temporaria += 1;
    }

    MAIN_CHARACTER.VIDA = 20 + (rand() % 20);
    MAIN_CHARACTER.AGILIDADE = 10 + (rand() % 20);
    MAIN_CHARACTER.DEFESA = 10 + (rand() % 10);
    MAIN_CHARACTER.ATAQUE = 15 + (rand() % 20);
    MAIN_CHARACTER.CHARME = 10 + (rand() % 30);
    MAIN_CHARACTER.CARISMA = 20 + (rand() % 6);
    MAIN_CHARACTER.EXPERIENCIA = 0;
    SKILL_CHARACTER.TOTAL_MANA = 120 + (rand() % 61);
    SKILL_CHARACTER.skill_points = 0;

    SKILL_CHARACTER.INSPIRACAO = 0;
    SKILL_CHARACTER.SUMMON_TRETA = 0;
    SKILL_CHARACTER.BE_DWARF = 0;
    SKILL_CHARACTER.BE_GIANT = 0;

    if (nomainus(nome_personagem, "DISNEY", '\0') == 0)
        MAIN_CHARACTER.CHARME = -9990;

    else if ((nomainus(nome_personagem, "FRANCIS", '\0') == 0) || (nomainus(nome_personagem, "TITO", '\0') == 0))
        MAIN_CHARACTER.CHARME = 9990;

    else if ((nomainus(nome_personagem, "JICTYVOO", '\0') == 0) || (nomainus(nome_personagem, "JOAO", '\0') == 0)) {
        MAIN_CHARACTER.ATAQUE = 40;
        MAIN_CHARACTER.DEFESA = 30;
    } else if ((nomainus(nome_personagem, "ABEL", '\0') == 0) || (nomainus(nome_personagem, "HOBBIT", '\0') == 0))
        MAIN_CHARACTER.AGILIDADE = 30;

    else if (nomainus(nome_personagem, "VINICIUS", '\0') == 0)
        MAIN_CHARACTER.CARISMA = 500;

    MAIN_CHARACTER.NOME_PERSONAGEM = nome_personagem;
    MAIN_CHARACTER.NIVEL = 0;

    MAIN_PERSONAGEM.francis_essence = 0;
    MAIN_PERSONAGEM.elixir = 1;
    MAIN_PERSONAGEM.aumenta_atk = 0;
    MAIN_PERSONAGEM.aumenta_def = 0;
    MAIN_PERSONAGEM.aumenta_agi = 0;

    status_regen(&MAIN_CHARACTER, &HAVE_CHARACTER, &SKILL_CHARACTER);
}

void apresenta_status() {
    limpa_tela();
    fprintf(stdout, "VIDA: %ld/%ld\n", HAVE_CHARACTER.have_life, MAIN_CHARACTER.VIDA);
    fprintf(stdout, "AGILIDADE: %ld/%ld\n", HAVE_CHARACTER.have_agility, MAIN_CHARACTER.AGILIDADE);
    fprintf(stdout, "DEFESA: %ld/%ld\n", HAVE_CHARACTER.have_defense, MAIN_CHARACTER.DEFESA);
    fprintf(stdout, "ATAQUE: %ld/%ld\n", HAVE_CHARACTER.have_attack, MAIN_CHARACTER.ATAQUE);
    fprintf(stdout, "CHARME: %ld/%ld\n", HAVE_CHARACTER.have_luck, MAIN_CHARACTER.CHARME);
    fprintf(stdout, "CARISMA: %ld/%ld\n", HAVE_CHARACTER.have_charism, MAIN_CHARACTER.CARISMA);
    fprintf(stdout, "NIVEL: %lu\n", MAIN_CHARACTER.NIVEL);
    fprintf(stdout, "NOME: %s\n", MAIN_CHARACTER.NOME_PERSONAGEM);
    char exp_quer;
    tecla_buff();
    printf("\nPressione ENTER para continuar. . . ");
    exp_quer = (char) getchar();
    if (exp_quer == 'e') {
        limpa_tela();
        fprintf(stdout, "EXPERIENCIA: %lu\n", MAIN_CHARACTER.EXPERIENCIA);
        continuar_enter();
    }
    tecla_buff();
}

void apresenta_companheiros(status_friends *COMPANHEIROS) {

    unsigned short int temporaria = 0;
    unsigned short int controle = 0;

    limpa_tela();
    while (temporaria < 4) {
        if (COMPANHEIROS->existentes[temporaria] != derrota) {
            fprintf(stdout, "%c)\n", 65 + temporaria);
            fprintf(stdout, "VIDA: %ld/%ld\n", COMPANHEIROS->THEY_HAVE[temporaria].have_life,
                    COMPANHEIROS->THEY_TOTAL[temporaria].VIDA);
            fprintf(stdout, "AGILIDADE: %ld/%ld\n", COMPANHEIROS->THEY_HAVE[temporaria].have_agility,
                    COMPANHEIROS->THEY_TOTAL[temporaria].AGILIDADE);
            fprintf(stdout, "DEFESA: %ld/%ld\n", COMPANHEIROS->THEY_HAVE[temporaria].have_defense,
                    COMPANHEIROS->THEY_TOTAL[temporaria].DEFESA);
            fprintf(stdout, "ATAQUE: %ld/%ld\n", COMPANHEIROS->THEY_HAVE[temporaria].have_attack,
                    COMPANHEIROS->THEY_TOTAL[temporaria].ATAQUE);
            fprintf(stdout, "CHARME: %ld/%ld\n", COMPANHEIROS->THEY_HAVE[temporaria].have_luck,
                    COMPANHEIROS->THEY_TOTAL[temporaria].CHARME);
            fprintf(stdout, "CARISMA: %ld/%ld\n", COMPANHEIROS->THEY_HAVE[temporaria].have_charism,
                    COMPANHEIROS->THEY_TOTAL[temporaria].CARISMA);
            fprintf(stdout, "NIVEL: %lu\n", COMPANHEIROS->THEY_TOTAL[temporaria].NIVEL);
            fprintf(stdout, "NOME: %s\n\n\n", COMPANHEIROS->THEY_TOTAL[temporaria].NOME_PERSONAGEM);
            controle += 1;
        }
        temporaria += 1;
    }
    if (controle == 0)
        fprintf(stdout, "Ninguem gosta de voce, ta sozinho\n");
    char vai_embora;
    tecla_buff();
    printf("\nPressione ENTER para continuar. . . ");
    vai_embora = (char) getchar();
    if ((vai_embora == 'a' || vai_embora == 'A') && COMPANHEIROS->existentes[0] != derrota) {
        limpa_tela();
        COMPANHEIROS->existentes[0] = derrota;
        fprintf(stdout, "%s foi embora\n", COMPANHEIROS->THEY_TOTAL[0].NOME_PERSONAGEM);
        continuar_enter();
    } else if ((vai_embora == 'b' || vai_embora == 'B') && COMPANHEIROS->existentes[1] != derrota) {
        limpa_tela();
        COMPANHEIROS->existentes[1] = derrota;
        fprintf(stdout, "%s foi embora\n", COMPANHEIROS->THEY_TOTAL[1].NOME_PERSONAGEM);
        continuar_enter();
    } else if ((vai_embora == 'c' || vai_embora == 'C') && COMPANHEIROS->existentes[2] != derrota) {
        limpa_tela();
        COMPANHEIROS->existentes[2] = derrota;
        fprintf(stdout, "%s foi embora\n", COMPANHEIROS->THEY_TOTAL[2].NOME_PERSONAGEM);
        continuar_enter();
    } else if ((vai_embora == 'd' || vai_embora == 'D') && COMPANHEIROS->existentes[3] != derrota) {
        limpa_tela();
        COMPANHEIROS->existentes[3] = derrota;
        fprintf(stdout, "%s foi embora\n", COMPANHEIROS->THEY_TOTAL[3].NOME_PERSONAGEM);
        continuar_enter();
    }
}

void apresenta_mochila() {
    fprintf(stdout, "Conteudo da Mochila:\n");
    if (MAIN_PERSONAGEM.francis_essence > 0)
        fprintf(stdout, "1.Essencia de Francis (x%hu)\n", MAIN_PERSONAGEM.francis_essence);
    if (MAIN_PERSONAGEM.elixir > 0)
        fprintf(stdout, "2.ELixir (x%hu)\n", MAIN_PERSONAGEM.elixir);
    if (MAIN_PERSONAGEM.aumenta_atk > 0)
        fprintf(stdout, "3.Ataque Booster (x%hu)\n", MAIN_PERSONAGEM.aumenta_atk);
    if (MAIN_PERSONAGEM.aumenta_def > 0)
        fprintf(stdout, "4.Defesa Booster (x%hu)\n", MAIN_PERSONAGEM.aumenta_def);
    if (MAIN_PERSONAGEM.aumenta_agi > 0)
        fprintf(stdout, "5.Agilidade Booster (x%hu)\n", MAIN_PERSONAGEM.aumenta_agi);
}

unsigned short int critical_hit(char nome_defensor[], tem_status ele_tem, long int *porcentagem_critico) {
    unsigned int variacao;
    unsigned int critical_chance;
    variacao = (unsigned int) strlen(nome_defensor);
    critical_chance = (unsigned int) (ele_tem.have_attack + ele_tem.have_defense);
    if (critical_chance <= 2)
        return derrota;
    if (ele_tem.have_agility > 1)
        critical_chance = (unsigned int) (ele_tem.have_agility * variacao) / critical_chance;
    *porcentagem_critico = 1 + rand() % 50;

    if (critical_chance <= 2)
        return derrota;

    long int tera_critico;
    tera_critico = rand() % (critical_chance * (*porcentagem_critico));
    if (tera_critico <= critical_chance)
        return vitoria;
    return derrota;
}

long int calculo_dano(tem_status atacante, tem_status defensor, char nome_defensor[]) {
    long int dano = 0;
    long int suporte_agilidade;
    unsigned long int copia;
    suporte_agilidade = atacante.have_agility - defensor.have_agility;
    dano = (long int) (atacante.have_attack * 1.15) - defensor.have_defense + suporte_agilidade * 0.50;

    if (dano < 0) {
        fprintf(stdout, "A defesa de %s eh alta demais!\n", nome_defensor);
        return 0;
    }
    if (critical_hit(nome_defensor, atacante, &suporte_agilidade) == vitoria) {
        copia = dano;
        fprintf(stdout, "%s sofreu %ld%% a mais de dano critico\n", nome_defensor, suporte_agilidade);
        dano = dano + (copia * (suporte_agilidade / 100));
    }
    return dano;
}

void drop_itens(unsigned short int chance, char nome_vilao[]) {
    unsigned short int controle;
    controle = rand() % chance;
    if (controle == 0 || (controle >= 3 && controle <= 5)) {
        fprintf(stdout, "%s dropou Elixir\n", nome_vilao);
        MAIN_PERSONAGEM.elixir = MAIN_PERSONAGEM.elixir + 1;
    } else if (controle == chance - 1) {
        fprintf(stdout, "%s dropou Tito's Essence\n", nome_vilao);
        MAIN_PERSONAGEM.francis_essence = MAIN_PERSONAGEM.francis_essence + 1;
    } else if (controle == 1 || controle == chance - 3) {
        fprintf(stdout, "%s dropou Ataque Booster\n", nome_vilao);
        MAIN_PERSONAGEM.aumenta_atk = MAIN_PERSONAGEM.aumenta_atk + 1;
    } else if (controle == 2 || controle == chance - 2) {
        fprintf(stdout, "%s dropou Defesa Booster\n", nome_vilao);
        MAIN_PERSONAGEM.aumenta_def = MAIN_PERSONAGEM.aumenta_def + 1;
    } else if (controle == 6 || controle == chance - 7) {
        fprintf(stdout, "%s dropou Agilidade Booster\n", nome_vilao);
        MAIN_PERSONAGEM.aumenta_agi = MAIN_PERSONAGEM.aumenta_agi + 1;
    } else
        fprintf(stdout, "%s era universitario, sem itens\n", nome_vilao);
}

int acoes_player(unsigned short int controle) {
    int escolha;
    controle = 0;
    do {
        if (controle != 0)
            limpa_tela();
        fprintf(stdout, "\n [1] ATACAR\n [2] ESPECIAIS POWERS\n [3] SEDUZIR\n [4] MOCHILA\n [5] CHORAR\n--> ");
        tecla_buff();
        controle = controle + 1;
    } while (!scanf("%d", &escolha) || escolha < 1 || escolha > 5);
    if (escolha == 1)
        return atacar;
    else if (escolha == 2)
        return skill_attack;
    else if (escolha == 3)
        return conversar;
    else if (escolha == 4)
        return mochila;
    else
        return chorar;
}

int inic_menu() {
    int menu_escolha;
    do {
        tecla_buff();
        limpa_tela();
        printf(" 1- JOGAR\n 2- COMO JOGAR\n 3- SAIR\n--> ");
    } while (!scanf("%d", &menu_escolha) || menu_escolha < 1 || menu_escolha > 3);
    tecla_buff();
    return menu_escolha;
}

void iniciar() {
    limpa_tela();
    fprintf(stdout, "Era uma vez, uma pessoa,\n");
    fprintf(stdout, "que vivia absorta\nate estudar computacao,\n");
    fprintf(stdout, "onde seus olhos\nencheram-se de emocao...\n\n");
    fprintf(stdout, "Ela era linda, era bela,\ntao doce e singela\n");
    fprintf(stdout, "mas tao distante ficava\naos desafios que nosso guerreiro enfrentava...\n\n");
    fprintf(stdout, "\nOi, quer jogar?\n");
    continuar_enter();
    limpa_tela();
}

unsigned short int teste_fuga(unsigned short int chance) {
    if (chance == 100000)
        return chorar;
    unsigned short int conseguido;
    conseguido = MAIN_CHARACTER.NIVEL + (rand() % (HAVE_CHARACTER.have_agility + (rand() % 5)));
    if (conseguido >= chance)
        return derrota;
    else
        return chorar;
}

unsigned short int teste_evasao(tem_status efetuador, tem_status atacante, char nome_evasor[]) {
    unsigned long int evadiu = derrota;
    if (efetuador.have_agility > atacante.have_agility) {
        evadiu = efetuador.have_agility - atacante.have_agility;
        while (evadiu > 100)
            evadiu = evadiu / (2 + (rand() % 2));
        unsigned long int temporaria = 1 + rand() % 100;
        if (temporaria <= evadiu) {
            fprintf(stdout, "%s evadiu do golpe\n", nome_evasor);
            return vitoria;
        } else
            return derrota;
    }
    return derrota;
}

void selecao_mochila(atributos *PRINCIPAL, mochilinha *O_PERSONAGEM, tem_status *PERTEM, the_skills *SKILL_PERSONAGEM,
                     char vilao_frases[][100], short int numero) {
    unsigned short int escolha;
    do {
        tecla_buff();
        limpa_tela();
        apresenta_mochila();
        fprintf(stdout, "0.Sair\n --> ");
    } while (!fscanf(stdin, "%hu", &escolha) || escolha < 0 || escolha > 5);
    limpa_tela();
    unsigned short int temporaria = 0;
    if (escolha == 1 && O_PERSONAGEM->francis_essence > 0) {
        unsigned short int mais_charme = 10 + rand() % 10;
        temporaria = 1;
        PRINCIPAL->CHARME = PRINCIPAL->CHARME + mais_charme;
        PERTEM->have_luck = PERTEM->have_luck + mais_charme;
        O_PERSONAGEM->francis_essence = O_PERSONAGEM->francis_essence - 1;
        fprintf(stdout, "Essencia de Francis consumida\t\t +%hu em CHARME\n", mais_charme);
    } else if (escolha == 2 && O_PERSONAGEM->elixir > 0) {
        status_regen(&(*PRINCIPAL), &(*PERTEM), &(*SKILL_PERSONAGEM));
        temporaria = 2;
        O_PERSONAGEM->elixir = O_PERSONAGEM->elixir - 1;
        fprintf(stdout, "Vida restaurada e atributos retaurados!\n");
    } else if (escolha == 3 && O_PERSONAGEM->aumenta_atk > 0) {
        unsigned short int mais_ataque = 5 + rand() % 5;
        temporaria = 3;
        PRINCIPAL->ATAQUE = PRINCIPAL->ATAQUE + mais_ataque;
        PERTEM->have_attack = PERTEM->have_attack + mais_ataque;
        O_PERSONAGEM->aumenta_atk = O_PERSONAGEM->aumenta_atk - 1;
        fprintf(stdout, "Booster de Ataque consumido\t\t +%hu em ATAQUE\n", mais_ataque);
    } else if (escolha == 4 && O_PERSONAGEM->aumenta_def > 0) {
        unsigned short int mais_defesa = 5 + rand() % 5;
        temporaria = 4;
        PRINCIPAL->DEFESA = PRINCIPAL->DEFESA + mais_defesa;
        PERTEM->have_defense = PERTEM->have_defense + mais_defesa;
        O_PERSONAGEM->aumenta_def = O_PERSONAGEM->aumenta_def - 1;
        fprintf(stdout, "Booster de Defesa consumido\t\t +%hu em DEFESA\n", mais_defesa);
    } else if (escolha == 5 && O_PERSONAGEM->aumenta_agi > 0) {
        unsigned short int mais_agilidade = 5 + rand() % 5;
        temporaria = 5;
        PRINCIPAL->AGILIDADE = PRINCIPAL->AGILIDADE + mais_agilidade;
        PERTEM->have_agility = PERTEM->have_agility + mais_agilidade;
        O_PERSONAGEM->aumenta_agi = O_PERSONAGEM->aumenta_agi - 1;
        fprintf(stdout, "Booster de Agilidade consumido\t\t +%hu em AGILIDADE\n", mais_agilidade);
    }
    if (temporaria == 0)
        fprintf(stdout, "Sem item requisitado\n");
    if (escolha != 0)
        continuar_enter();
    tecla_buff();
    limpa_tela();
    fprintf(stdout, "%s\n", vilao_frases[rand() % numero]);
}

void skill_aleatorio(the_skills *SKILL_COMMENEMY, atributos MAIN_PERSONAGEM) {
    unsigned short int sorteio;

    SKILL_COMMENEMY->INSPIRACAO = 0;
    SKILL_COMMENEMY->SUMMON_TRETA = 0;
    SKILL_COMMENEMY->BE_DWARF = 0;
    SKILL_COMMENEMY->BE_GIANT = 0;

    while (MAIN_PERSONAGEM.NIVEL > 0) {
        sorteio = 1 + rand() % 4;
        switch (sorteio) {
            case 1:
                SKILL_COMMENEMY->INSPIRACAO = SKILL_COMMENEMY->INSPIRACAO + 1;
                MAIN_PERSONAGEM.NIVEL = MAIN_PERSONAGEM.NIVEL - 1;
                break;

            case 2:
                SKILL_COMMENEMY->SUMMON_TRETA = SKILL_COMMENEMY->SUMMON_TRETA + 1;
                MAIN_PERSONAGEM.NIVEL = MAIN_PERSONAGEM.NIVEL - 1;
                break;

            case 3:
                SKILL_COMMENEMY->BE_DWARF = SKILL_COMMENEMY->BE_DWARF + 1;
                MAIN_PERSONAGEM.NIVEL = MAIN_PERSONAGEM.NIVEL - 1;
                break;

            case 4:
                SKILL_COMMENEMY->BE_GIANT = SKILL_COMMENEMY->BE_GIANT + 1;
                MAIN_PERSONAGEM.NIVEL = MAIN_PERSONAGEM.NIVEL - 1;
                break;
        }
    }
}

unsigned short int lista_companheiros(status_friends *COMPANHEIROS, atributos *COMMENEMY) {
    unsigned short int temporaria = 0;
    while (temporaria < 4) {
        if (COMPANHEIROS->existentes[temporaria] == derrota)
            break;
        temporaria = temporaria + 1;
    }
    if (temporaria == 4) {
        fprintf(stdout, "Incapaz de converter mais inimigos\n");
        continuar_enter();
        limpa_tela();
        return derrota;
    }
    char *nome = (char *) calloc(25, sizeof(char));
    /*strcpy(nome, COMMENEMY -> NOME_PERSONAGEM);*/
    fprintf(stdout, "Nomee-me meu amigo\n__.> ");
    fgets(nome, 25, stdin);
    nome[strlen(nome) - 1] = '\0';
    limpa_tela();
    tecla_buff();
    COMPANHEIROS->THEY_TOTAL[temporaria].NOME_PERSONAGEM = nome;
    COMPANHEIROS->THEY_TOTAL[temporaria].VIDA = COMMENEMY->VIDA;
    COMPANHEIROS->THEY_TOTAL[temporaria].AGILIDADE = COMMENEMY->AGILIDADE;
    COMPANHEIROS->THEY_TOTAL[temporaria].DEFESA = COMMENEMY->DEFESA;
    COMPANHEIROS->THEY_TOTAL[temporaria].ATAQUE = COMMENEMY->ATAQUE;
    COMPANHEIROS->THEY_TOTAL[temporaria].CHARME = COMMENEMY->CHARME;
    COMPANHEIROS->THEY_TOTAL[temporaria].CARISMA = COMMENEMY->CARISMA;
    COMPANHEIROS->THEY_TOTAL[temporaria].EXPERIENCIA = COMMENEMY->EXPERIENCIA;
    COMPANHEIROS->THEY_TOTAL[temporaria].NIVEL = COMMENEMY->NIVEL;

    the_skills SKILL_COMMENEMY;
    SKILL_COMMENEMY.TOTAL_MANA = ((50 * MAIN_CHARACTER.NIVEL) + rand() % 25);
    skill_aleatorio(&SKILL_COMMENEMY, MAIN_CHARACTER);

    status_regen(&(COMPANHEIROS->THEY_TOTAL[temporaria]), &(COMPANHEIROS->THEY_HAVE[temporaria]), &SKILL_COMMENEMY);
    COMPANHEIROS->existentes[temporaria] = vitoria;
    fprintf(stdout, "Eh uma honra unir-me a voce\n");
    return vitoria;
}

void win_battle(atributos *MAIN_PERSONAGEM, atributos *COMMENEMY, unsigned long int chance) {
    long int experiencia_ganha;
    if (COMMENEMY->EXPERIENCIA > 2)
        experiencia_ganha = (long int) ((COMMENEMY->EXPERIENCIA / 2) + rand() % (COMMENEMY->EXPERIENCIA / 2));
    else
        experiencia_ganha = (long int) COMMENEMY->EXPERIENCIA;

    MAIN_PERSONAGEM->EXPERIENCIA = (long int) MAIN_PERSONAGEM->EXPERIENCIA + experiencia_ganha;
    fprintf(stdout, "%ld de experiencia ganha\n", experiencia_ganha);
    if (verifica_upa(&MAIN_CHARACTER) == upa_nivel)
        fprintf(stdout, "Voce evoluiu para o nivel %lu!\n", MAIN_PERSONAGEM->NIVEL);
    drop_itens(chance, COMMENEMY->NOME_PERSONAGEM);
}

void seduzir_enemy(atributos *MAIN_PERSONAGEM, atributos *COMMENEMY, status_friends *COMPANHEIROS) {
    limpa_tela();
    fprintf(stdout, "Nossa, você realmente é charmoso(a), tens minha atenção\n");
    unsigned short int temporaria = 0;
    do {
        tecla_buff();
        if (temporaria != 0)
            limpa_tela();
        fprintf(stdout, "[1] Dê-me XP para batalhas futuras!\n[2] Acompanhe-me em minha jornada!\n--> ");
    } while (!fscanf(stdin, "%hu", &temporaria) || temporaria < 1 || temporaria > 2);
    limpa_tela();
    tecla_buff();

    switch (temporaria) {
        case 2:
            lista_companheiros(COMPANHEIROS, COMMENEMY);
            break;
    }
}

int conversa_diminui(atributos *PRINCIPAL, tem_status *PERTEM, tem_status *HAVE_PERSONAGEM, atributos *MAIN_PERSONAGEM,
                     status_friends *COMPANHEIROS, char vilao_frases[][100], unsigned short int numero) {
    if (HAVE_PERSONAGEM->have_luck < PERTEM->have_luck) {
        fprintf(stdout, "%s eh charmoso demais para seduzir\n", PRINCIPAL->NOME_PERSONAGEM);
        continuar_enter();
        return derrota;
    }
    fprintf(stdout, "%s\n", vilao_frases[rand() % numero]);
    unsigned short int mudanca = 1 + (rand() % 3);
    /*1 - Agilidade, 2 - Defesa*/
    switch (mudanca) {
        case 1:
            mudanca = 1 + (rand() % 7);
            PERTEM->have_agility = PERTEM->have_agility - mudanca;
            fprintf(stdout, "%hu Diminuido da agilidade de %s\n", mudanca, PRINCIPAL->NOME_PERSONAGEM);
            break;
        case 2:
            mudanca = 1 + (rand() % 7);
            PERTEM->have_defense = PERTEM->have_defense - mudanca;
            fprintf(stdout, "%hu Diminuido da defesa de %s\n", mudanca, PRINCIPAL->NOME_PERSONAGEM);
            break;
        default:
            fprintf(stdout, "%s: Nunca conseguira me derrotar\n", PRINCIPAL->NOME_PERSONAGEM);
            break;
    }
    if (PERTEM->have_defense <= 0) {
        seduzir_enemy(MAIN_PERSONAGEM, PRINCIPAL, COMPANHEIROS);
        return vitoria;
    }
    return derrota;

}

void attack_system(tem_status *VILOA, atributos VILAO, tem_status *HAVE_PERSONAGEM, atributos PERSONAGEM) {
    long int auxiliar;
    long int temporaria;

    auxiliar = calculo_dano((*VILOA), (*HAVE_PERSONAGEM), PERSONAGEM.NOME_PERSONAGEM);

    if (auxiliar > 1) { temporaria = (auxiliar / 2) + (rand() % (auxiliar / 2)); }
    else { temporaria = auxiliar; }

    if (temporaria > 0)
        auxiliar = teste_evasao((*HAVE_PERSONAGEM), (*VILOA), PERSONAGEM.NOME_PERSONAGEM);
    if (auxiliar != vitoria) {
        HAVE_PERSONAGEM->have_life = HAVE_PERSONAGEM->have_life - temporaria;
        if (temporaria > 0)
            fprintf(stdout, "%s infringiu %ld de Dano\n", VILAO.NOME_PERSONAGEM, temporaria);
    }

    auxiliar = calculo_dano((*HAVE_PERSONAGEM), (*VILOA), VILAO.NOME_PERSONAGEM);

    if (auxiliar > 1) { temporaria = (auxiliar / 2) + (rand() % (auxiliar / 2)); }
    else { temporaria = auxiliar; }

    if (temporaria > 0)
        auxiliar = teste_evasao((*VILOA), (*HAVE_PERSONAGEM), VILAO.NOME_PERSONAGEM);
    if (auxiliar != vitoria) {
        VILOA->have_life = VILOA->have_life - temporaria;
        if (temporaria > 0)
            fprintf(stdout, "%s infringiu %ld de Dano\n", PERSONAGEM.NOME_PERSONAGEM, temporaria);
    }
}

unsigned short int character_skills(tem_status *HAVE_PERSONAGEM, atributos PERSONAGEM, the_skills *SKILL_PERSONAGEM,
                                    unsigned short int *contador) {
    unsigned short int escolha;
    do {
        tecla_buff();
        limpa_tela();
        if (SKILL_PERSONAGEM->INSPIRACAO > 0)
            fprintf(stdout, "[1] INSPIRACAO (%d)\n", (30 + (15 * SKILL_PERSONAGEM->INSPIRACAO)));
        if (SKILL_PERSONAGEM->SUMMON_TRETA > 0)
            fprintf(stdout, "[2] INVOCAR TRETA (%d)\n", (40 + (10 * SKILL_PERSONAGEM->SUMMON_TRETA)));
        if (SKILL_PERSONAGEM->BE_DWARF > 0)
            fprintf(stdout, "[3] ABEL' POWER (%d)\n", (50 + (10 * SKILL_PERSONAGEM->BE_DWARF)));
        if (SKILL_PERSONAGEM->BE_GIANT > 0)
            fprintf(stdout, "[4] AURELIO'S POWER (%d)\n", (50 + (10 * SKILL_PERSONAGEM->BE_GIANT)));
        fprintf(stdout, "[0] SAIR\n");
        fprintf(stdout, "MANA: %ld/%ld\n--> ", SKILL_PERSONAGEM->have_mana, SKILL_PERSONAGEM->TOTAL_MANA);
    } while (!fscanf(stdin, "%hu", &escolha) || escolha < 0 || escolha > 4);
    tecla_buff();
    switch (escolha) {
        case 0:
            fprintf(stdout, "Nenhuma SKill utilizada!\n");
            break;

        case 1:
            if (SKILL_PERSONAGEM->INSPIRACAO <= 0) {
                fprintf(stdout, "Skill nao esta ativa!\n");
                return derrota;
            } else if (SKILL_PERSONAGEM->have_mana < (30 + (15 * SKILL_PERSONAGEM->INSPIRACAO))) {
                fprintf(stdout, "Sem mana suficiente!\n");
                return derrota;
            }
            escolha = (21 + (rand() % 12)) + ((15 + (rand() % 19)) * (0.15 * SKILL_PERSONAGEM->INSPIRACAO));
            HAVE_PERSONAGEM->have_charism = HAVE_PERSONAGEM->have_charism + escolha;
            fprintf(stdout, "Carisma aumentada em %hu", escolha);
            contador[0] = 3 + SKILL_PERSONAGEM->INSPIRACAO;
            SKILL_PERSONAGEM->have_mana = SKILL_PERSONAGEM->have_mana - (30 + (15 * SKILL_PERSONAGEM->INSPIRACAO));
            break;

        case 2:
            if (SKILL_PERSONAGEM->SUMMON_TRETA <= 0) {
                fprintf(stdout, "Skill nao esta ativa!\n");
                return derrota;
            } else if (SKILL_PERSONAGEM->have_mana < (40 + (10 * SKILL_PERSONAGEM->SUMMON_TRETA))) {
                fprintf(stdout, "Sem mana suficiente!\n");
                return derrota;
            }
            escolha = (21 + (rand() % 12)) + ((15 + (rand() % 19)) * (0.15 * SKILL_PERSONAGEM->SUMMON_TRETA));
            contador[1] = 2 + SKILL_PERSONAGEM->SUMMON_TRETA;
            SKILL_PERSONAGEM->have_mana = SKILL_PERSONAGEM->have_mana - (40 + (10 * SKILL_PERSONAGEM->SUMMON_TRETA));
            break;

        case 3:
            if (SKILL_PERSONAGEM->BE_DWARF <= 0) {
                fprintf(stdout, "Skill nao esta ativa!\n");
                return derrota;
            } else if (SKILL_PERSONAGEM->have_mana < (50 + (10 * SKILL_PERSONAGEM->BE_DWARF))) {
                fprintf(stdout, "Sem mana suficiente!\n");
                return derrota;
            }
            escolha = (17 + (rand() % 22)) + ((17 + (rand() % 22)) * (0.35 * SKILL_PERSONAGEM->BE_DWARF));
            HAVE_PERSONAGEM->have_agility = HAVE_PERSONAGEM->have_agility + escolha;
            HAVE_PERSONAGEM->have_attack = HAVE_PERSONAGEM->have_attack - escolha;
            fprintf(stdout, "Agilidade incrementada e Ataque decrementado em %hu\n", escolha);
            contador[2] = 2 + SKILL_PERSONAGEM->BE_DWARF;
            SKILL_PERSONAGEM->have_mana = SKILL_PERSONAGEM->have_mana - (50 + (10 * SKILL_PERSONAGEM->BE_DWARF));
            break;

        case 4:
            if (SKILL_PERSONAGEM->BE_GIANT <= 0) {
                fprintf(stdout, "Skill nao esta ativa!\n");
                return derrota;
            } else if (SKILL_PERSONAGEM->have_mana < (50 + (10 * SKILL_PERSONAGEM->BE_GIANT))) {
                fprintf(stdout, "Sem mana suficiente!\n");
                return derrota;
            }
            escolha = (17 + (rand() % 22)) + ((17 + (rand() % 22)) * (0.35 * SKILL_PERSONAGEM->BE_GIANT));
            HAVE_PERSONAGEM->have_attack = HAVE_PERSONAGEM->have_attack + escolha;
            HAVE_PERSONAGEM->have_agility = HAVE_PERSONAGEM->have_agility - escolha;
            fprintf(stdout, "Ataque incrementado e Agilidade decrementada em %hu\n", escolha);
            contador[3] = 2 + SKILL_PERSONAGEM->BE_GIANT;
            SKILL_PERSONAGEM->have_mana = SKILL_PERSONAGEM->have_mana - (50 + (10 * SKILL_PERSONAGEM->BE_GIANT));
            break;
    }
    return vitoria;
}

unsigned short int
controle_skill_duracao(unsigned short int contador[], tem_status *HAVE_PERSONAGEM, atributos PERSONAGEM) {
    /*retorna 0 se não perdeu efeito, 1 se a primeira skill perdeu efeito e assim por diante*/
    if (contador[0] > 0) {
        contador[0] = contador[0] - 1;
        if (contador[0] != 0)
            fprintf(stdout, "INSPIRACAO permanecera ativa por mais %hu turnos\n", contador[0]);
        else if (contador[0] == 0) {
            HAVE_PERSONAGEM->have_charism = PERSONAGEM.CARISMA;
            fprintf(stdout, "INSPIRACAO perdeu o efeito\n");
        }
        if (contador[1] <= 0 || contador[2] <= 0 || contador[3] <= 0)
            return contador[0];
    }
    if (contador[1] > 0) {
        contador[1] = contador[1] - 1;
        if (contador[1] != 0)
            fprintf(stdout, "INVOCAR TRETA permanecera ativa por mais %hu turnos\n", contador[1]);
        else if (contador[1] == 0) {
            HAVE_PERSONAGEM->have_charism = PERSONAGEM.CARISMA;
            fprintf(stdout, "INVOCAR TRETA perdeu o efeito\n");
        }
        if (contador[2] <= 0 || contador[3] <= 0)
            return contador[1];
    }
    if (contador[2] > 0) {
        contador[2] = contador[2] - 1;
        if (contador[2] != 0)
            fprintf(stdout, "ABEL'S POWER permanecera ativa por mais %hu turnos\n", contador[2]);
        else if (contador[2] == 0) {
            HAVE_PERSONAGEM->have_agility = PERSONAGEM.AGILIDADE;
            HAVE_PERSONAGEM->have_attack = PERSONAGEM.ATAQUE;
            fprintf(stdout, "ABEL'S POWER perdeu o efeito\n");
        }
        if (contador[3] <= 0)
            return contador[2];
    }
    if (contador[3] > 0) {
        contador[3] = contador[3] - 1;
        if (contador[3] != 0)
            fprintf(stdout, "AURELIO'S POWER permanecera ativa por mais %hu turnos\n", contador[3]);
        else if (contador[3] == 0) {
            HAVE_PERSONAGEM->have_agility = PERSONAGEM.AGILIDADE;
            HAVE_PERSONAGEM->have_attack = PERSONAGEM.ATAQUE;
            fprintf(stdout, "AURELIO'S POWER perdeu o efeito\n");
        }
        return contador[3];
    }
    return -1;
}

unsigned short int
combat_system(atributos VILAO, tem_status VILOA, char vilao_frases[][100], unsigned short int chance, short int numero,
              status_friends *COMPANHEIROS) {
    unsigned short int escolha;
    unsigned short int controle = 0;
    unsigned short int contador[4] = {0, 0, 0, 0};

    do {

        if (controle_skill_duracao(contador, &HAVE_CHARACTER, MAIN_CHARACTER) == 0)
            continuar_enter();
        escolha = acoes_player(controle);
        limpa_tela();
        switch (escolha) {
            case atacar:
                attack_system(&VILOA, VILAO, &HAVE_CHARACTER, MAIN_CHARACTER);
                fprintf(stdout, "%s\n\n", vilao_frases[rand() % numero]);
                printf("%s LIFE: %ld/%ld\n%s LIFE: %ld/%ld\n", MAIN_CHARACTER.NOME_PERSONAGEM, HAVE_CHARACTER.have_life,
                       MAIN_CHARACTER.VIDA, VILAO.NOME_PERSONAGEM, VILOA.have_life, VILAO.VIDA);
                if (HAVE_CHARACTER.have_life <= 0) {
                    fprintf(stdout, "GAME OVER\n");
                    return derrota;
                }
                break;

            case skill_attack:
                character_skills(&HAVE_CHARACTER, MAIN_CHARACTER, &SKILL_CHARACTER, contador);
                continuar_enter();
                limpa_tela();
                break;

            case conversar:
                if (conversa_diminui(&VILAO, &VILOA, &HAVE_CHARACTER, &MAIN_CHARACTER, COMPANHEIROS, vilao_frases,
                                     numero) == vitoria)
                    VILOA.have_life = 0;

                break;

            case mochila:
                selecao_mochila(&MAIN_CHARACTER, &MAIN_PERSONAGEM, &HAVE_CHARACTER, &SKILL_CHARACTER, vilao_frases,
                                numero);
                break;

            case chorar:
                if (teste_fuga(chance) == derrota) {
                    fprintf(stdout, "Vergonha pra voce, pro seu cachorro, e pra sua PAIXAO!\n");
                    return derrota;
                } else
                    fprintf(stdout, "%s\n", vilao_frases[rand() % numero]);
                break;
        }

        controle++;
    } while (VILOA.have_life > 0 && HAVE_CHARACTER.have_life > 0);

    HAVE_CHARACTER.have_agility = MAIN_CHARACTER.AGILIDADE;
    HAVE_CHARACTER.have_attack = MAIN_CHARACTER.ATAQUE;
    HAVE_CHARACTER.have_charism = MAIN_CHARACTER.CARISMA;

    if (VILOA.have_life <= 0)
        return vitoria;
    else if (HAVE_CHARACTER.have_life <= 0)
        return derrota;
    return vitoria;
}

unsigned short int enemy_common(status_friends *COMPANHEIROS) {
    char enemy_name[][25] = {"Kuporig", "Freaky", "Kimataro", "Shagba", "Chimas", "Cielma"};
    atributos COMMENEMY;
    COMMENEMY.VIDA = ((MAIN_CHARACTER.VIDA / 2) + rand() % (MAIN_CHARACTER.VIDA / 2));
    COMMENEMY.AGILIDADE = ((MAIN_CHARACTER.AGILIDADE / 2) + rand() % (MAIN_CHARACTER.AGILIDADE / 2));
    COMMENEMY.DEFESA = ((MAIN_CHARACTER.DEFESA / 2) + rand() % (MAIN_CHARACTER.DEFESA / 2));
    COMMENEMY.ATAQUE = ((MAIN_CHARACTER.ATAQUE / 2) + rand() % (MAIN_CHARACTER.ATAQUE / 2));
    COMMENEMY.CHARME = ((MAIN_CHARACTER.CHARME / 2) + rand() % (MAIN_CHARACTER.CHARME / 2));
    COMMENEMY.CARISMA = ((MAIN_CHARACTER.CARISMA) + rand() % (MAIN_CHARACTER.CARISMA / 2));
    COMMENEMY.EXPERIENCIA = ((25 * MAIN_CHARACTER.NIVEL) + rand() % 30);
    COMMENEMY.NOME_PERSONAGEM = enemy_name[rand() % 6];

    the_skills SKILL_COMMENEMY;
    SKILL_COMMENEMY.TOTAL_MANA = ((30 * MAIN_CHARACTER.NIVEL) + rand() % 25);
    skill_aleatorio(&SKILL_COMMENEMY, MAIN_CHARACTER);

    tem_status HAVE_COMMENEMY;
    status_regen(&COMMENEMY, &HAVE_COMMENEMY, &SKILL_COMMENEMY);

    char frases_vilao[][100] = {"Eu vou matar voce!\n", "Suas emocoes sao putridas!\n",
                                "Perceba que suas acoes so pioram tudo!\n", "Por que nao a(o) deixa em paz!?\n",
                                "Porei voce no lugar que merece!\n"};
    fprintf(stdout, "%s\n", frases_vilao[rand() % 5]);
    if (combat_system(COMMENEMY, HAVE_COMMENEMY, frases_vilao, (20 + rand() % 36), 5, COMPANHEIROS) == vitoria) {
        /*dando aumentando xp*/
        win_battle(&MAIN_CHARACTER, &COMMENEMY, (70 + rand() % 35));
        return vitoria;
    } else
        return derrota;
}

unsigned short int NALLAS_boss(status_friends *COMPANHEIROS) {
    limpa_tela();
    printf("NALLAS: Percebi que congelaste com aquela estupefata visao,\nMas alcanca-la nao ira ");
    printf("es apenas uma linda ilusao pois minha ela sera\n");
    char nallas_frases[8][100] = {"Voce nunca podera me persuadir\n", "Sempre serei superior a voce\n",
                                  "Voce ja perdeu\n", "Voce esta comecando a me animar\n",
                                  "Nessa historia eh voce ou eu\n", "A batalha da paixao eh minha\n",
                                  "Prepare sua derrota!\n", "Prepare-se para morrer\n"};

    char vilao_name[] = "NALLAS";
    atributos NALLAS;
    NALLAS.VIDA = 140;
    NALLAS.AGILIDADE = 35;
    NALLAS.DEFESA = 20;
    NALLAS.EXPERIENCIA = 10000;
    NALLAS.ATAQUE = 30;
    NALLAS.CHARME = 40;
    NALLAS.CARISMA = 20;
    NALLAS.NOME_PERSONAGEM = vilao_name;


    the_skills SKILL_NALLAS;
    SKILL_NALLAS.TOTAL_MANA = ((50 * MAIN_CHARACTER.NIVEL) + rand() % 25);
    skill_aleatorio(&SKILL_NALLAS, MAIN_CHARACTER);

    tem_status HAVE_NALLAS;

    status_regen(&NALLAS, &HAVE_NALLAS, &SKILL_NALLAS);
    if (combat_system(NALLAS, HAVE_NALLAS, nallas_frases, 10000, 8, COMPANHEIROS) == vitoria) {
        /*dando aumentando xp*/
        win_battle(&MAIN_CHARACTER, &NALLAS, 10);

        save_game(COMPANHEIROS);
        return vitoria;
    } else
        return derrota;
}

void primeira_parte() {
    fprintf(stdout, "A vida eh trist");
}

unsigned short int menu_aventura(char historia_frases[], unsigned int trecho_historia, status_friends *COMPANHEIROS) {
    unsigned short int choices;
    do {
        tecla_buff();
        limpa_tela();
        fprintf(stdout, "%s\n", historia_frases);
        fprintf(stdout,
                "[1] CONTINUAR HISTORIA\n[2] TREINAR CONTRA MONSTROS\n[3] STATUS PERSONAGEM\n[4] DESCANSAR\n[5] SALVAR E SAIR\n--> ");
    } while (!fscanf(stdin, "%hu", &choices) || choices < 1 || choices > 5);
    tecla_buff();
    limpa_tela();
    if (choices == 1) {
        NALLAS_boss(COMPANHEIROS);
        continuar_enter();
    } else if (choices == 2) {
        choices = enemy_common(COMPANHEIROS);
        if (choices == derrota) {
            continuar_enter();
            return 5;
        }

        continuar_enter();
    } else if (choices == 3) {
        do {
            limpa_tela();
            tecla_buff();
            fprintf(stdout, "[1] VER STATUS\n[2] VERIFICAR COMPANHEIROS\n[3] UPDATE SKILLS\n--> ");
        } while (!fscanf(stdin, "%hu", &choices) || choices < 1 || choices > 3);
        tecla_buff();
        if (choices == 1)
            apresenta_status();
        else if (choices == 2)
            apresenta_companheiros(COMPANHEIROS);
        else
            while (upa_skill(&SKILL_CHARACTER, MAIN_CHARACTER) != derrota);
    } else if (choices == 4) {
        status_regen(&MAIN_CHARACTER, &HAVE_CHARACTER, &SKILL_CHARACTER);
        fprintf(stdout, "Status retaurados com sucesso\n");
        continuar_enter();
    } else if (choices == 5) {
        save_game(COMPANHEIROS);
        fprintf(stdout, "Game salvo com sucesso\n");
        continuar_enter();
    }

    return choices;
}

int main() {
    srand((unsigned) time NULL);
    int controle = 0;
    dados_save[26] = 1;
    status_friends COMPANHEIROS;
    for (controle = 0; controle < 4; controle = controle + 1)
        COMPANHEIROS.existentes[controle] = derrota;

    controle = 0;
    abertura();
    while (controle != 3) {
        controle = inic_menu();
        if (controle == 1) {
            int temporaria = load_game(&COMPANHEIROS);

            if (temporaria == vitoria) {
                do {
                    tecla_buff();
                    limpa_tela();
                    fprintf(stdout, "[%hu] NEW GAME\n", 1);
                    fprintf(stdout, "[%hu] LOAD GAME\n--> ", 2);
                } while (!fscanf(stdin, "%d", &controle) || controle < 1 || controle > 2);
            } else {
                do {
                    tecla_buff();
                    limpa_tela();
                    fprintf(stdout, "[%hu] NEW GAME\n--> ", 1);
                } while (!fscanf(stdin, "%d", &controle) || controle != 1);
            }
            tecla_buff();

            if (controle == 1) {
                iniciar();
                nome_player(&COMPANHEIROS);
                fprintf(stdout, "Personagem criado\n Estatisticas:\n");
                apresenta_status();
            } else {
                limpa_tela();
                fprintf(stdout, "Dados carregados com sucesso\n");
                continuar_enter();
            }
            if (dados_save[26] == 1)
                while (menu_aventura("Em uma pequena vila se encontra\n com doces paisagens a vista...\n",
                                     dados_save[17], &COMPANHEIROS) != 5);
            free(MAIN_CHARACTER.NOME_PERSONAGEM);
        } else if (controle == 2) {
            limpa_tela();
            fprintf(stdout,
                    "Digite os numeros correspondentes as acoes que deseja tomar\n escolha suas acoes e acate a zoeira\n");
            continuar_enter();
        }
    }
    return chorar;
}
