#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "data.h"

#define ERR_UNIT_COUNT "ERR_UNIT_COUNT"
#define ERR_ITEM_COUNT "ERR_ITEM_COUNT"
#define ERR_WRONG_ITEM "ERR_WRONG_ITEM"
#define ERR_SLOTS "ERR_SLOTS"

typedef struct {
    struct unit units[5];
    int top;
} ARMY;

typedef struct {
    int army;
    char att_name[MAX_NAME + 1];
    char item[MAX_NAME + 1];
    int item_number;
    char def_name[MAX_NAME + 1];
    int dmg;
} DAMAGE;

void initA(ARMY *s) {
    s->top = -1;
    for (int i = 0; i < 5; i++) {
        s->units[i].hp = 0;
        s->units[i].item1 = NULL;
        s->units[i].item2 = NULL;
        memset(s->units[i].name, 0, sizeof(s->units[i].name));
    }
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

void error (const char *msg) {
    printf("%s\n", msg);
    fflush(stdout);
    exit(0);
}


bool is_full(const ARMY *s) {
    return s->top == 4;
}

bool push(ARMY *s,UNIT value) {
    if (is_full(s)) {
        return false;
    }
    s->units[++(s->top)] = value;
    return true;
}


bool pop_at(ARMY *s, int index) {
    if (index < 0 || index > s->top) return false;

    for (int i = index; i < s->top; ++i) {
        s->units[i] = s->units[i + 1];
    }
    s->top--;
    return true;
}


bool peek_at(const ARMY *s, int index, UNIT *out) {
    if (index < 0 || index > s->top) {
        return false;
    }
    *out = s->units[index];
    return true;
}

void print_army(ARMY a, int num) {
    printf("Army %d\n", num);
    for(int i=0; i < a.top + 1; i++) {
        printf("Unit: %d\nName: %s\nHP: %d\n", i, a.units[i].name, a.units[i].hp);
        if(a.units[i].item1) {
            printf("Item %d: %s,%d,%d,%d,%d,%d\n", 1,
                a.units[i].item1->name,
                a.units[i].item1->att,
                a.units[i].item1->def,
                a.units[i].item1->slots,
                a.units[i].item1->range,
                a.units[i].item1->radius);
        }
        if(a.units[i].item2) {
            printf("Item %d: %s,%d,%d,%d,%d,%d\n", 2,
                a.units[i].item2->name,
                a.units[i].item2->att,
                a.units[i].item2->def,
                a.units[i].item2->slots,
                a.units[i].item2->range,
                a.units[i].item2->radius);
        }
        printf("\n");
    }
}

void print_units(ARMY a) {
    for(int i=0; i < a.top + 1; i++) {
        printf("%s,%d ", a.units[i].name, a.units[i].hp);
    }
    printf("\n");
}

const ITEM* find(const char* name) {
    for(int i=0; i<NUMBER_OF_ITEMS; i++) {
        if(strcasecmp(items[i].name, name) == 0) return &items[i];
    }
    return NULL;
}


bool check_slots(UNIT un) {
    int total_slots = 0;

    if (un.item1) {
        total_slots += un.item1->slots;
    }

    if (un.item2) {
        total_slots += un.item2->slots;
    }

    return total_slots <= 2;
}


int main(const int argc, char *argv[]) {
    ARMY armies[2];
    initA(&armies[0]);
    initA(&armies[1]);
    int max_rounds = (argc > 1) ? atoi(argv[1]) : -1;
    for(int army_num = 0; army_num < 2; army_num++) {
        int unit_count;
        scanf("%d", &unit_count);
        getchar();
        if (unit_count < 1 || unit_count > 5) {
            error(ERR_UNIT_COUNT);
            return 0;
        }

        for(int i = 0; i < unit_count; i++) {
            UNIT u = {.hp = 100, .item2 = NULL};
            char name[MAX_NAME + 1] = {0};
            char item1[MAX_NAME + 1] = {0};
            char item2[MAX_NAME + 1] = {0};

            char c;
            int items_read = 0, j = 0;
            while ((c = getchar()) != '\n' && c != EOF) {
                if (c == ' ') {
                    items_read++;
                    j = 0;
                } else {
                    if (items_read == 0) {
                        name[j] = c;
                        j++;
                    } else if (items_read == 1) {
                        item1[j] = c;
                        j++;
                    } else if (items_read == 2) {
                        item2[j] = c;
                        j++;
                    } else if (items_read >= 3) {
                        error(ERR_ITEM_COUNT);
                        return 0;
                    }
                }
            }
            items_read++;

            if (items_read < 2) {
                error("ERR_ITEM_COUNT");
                return 0;
            }

            strncpy(u.name, name, MAX_NAME);

            const ITEM* it = find(item1);
            if(!it) {
                error(ERR_WRONG_ITEM);
                return 0;
            }
            u.item1 = it;

            if(items_read > 2 && strlen(item2) > 0) {
                it = find(item2);
                if(!it) {
                    error(ERR_WRONG_ITEM);
                    return 0;
                }
                    u.item2 = it;
                }

            if(!check_slots(u)) {
                error(ERR_SLOTS);
                return 0;
                }

            if(!push(&armies[army_num], u)) {
                error(ERR_UNIT_COUNT);
                return 0;
            }
        }
    }


    print_army(armies[0], 1);
    print_army(armies[1], 2);
    int round = 0;
    while((max_rounds == -1 || round < max_rounds) && armies[0].top > -1 && armies[1].top > -1) {
        printf("Round %d\n", round + 1);
        printf("%d: ", 1);
        print_units(armies[0]);
        printf("%d: ", 2);
        print_units(armies[1]);
        DAMAGE dmg[100] = {0};
        int dmg_count = 0;
        for (int i = 0; i <= armies[0].top; i++) {
            UNIT attacker;
            if (peek_at(&armies[0], i, &attacker)) {
                if (attacker.item1) {
                    if (attacker.item1->range >= i) {
                        for (int j = 0; j <= attacker.item1->radius; j++) {
                            UNIT defender;
                            if (peek_at(&armies[1], j, &defender)) {
                                int de = 0;
                                if (defender.item1) {
                                    de += defender.item1->def;
                                }
                                if (defender.item2) {
                                    de += defender.item2->def;
                                }
                                const int d = max(attacker.item1 -> att - de, 1);
                                armies[1].units[j].hp -= d;
                                dmg[dmg_count].army = 1;
                                strncpy(dmg[dmg_count].att_name, attacker.name, MAX_NAME);
                                dmg[dmg_count].att_name[MAX_NAME] = '\0';
                                strncpy(dmg[dmg_count].item, attacker.item1->name, MAX_NAME);
                                dmg[dmg_count].item[MAX_NAME] = '\0';
                                dmg[dmg_count].item_number = 1;
                                strncpy(dmg[dmg_count].def_name, defender.name, MAX_NAME);
                                dmg[dmg_count].def_name[MAX_NAME] = '\0';
                                dmg[dmg_count].dmg = d;
                                dmg_count++;
                            }
                        }
                    }
                }
                if (attacker.item2) {
                    if (attacker.item2 -> range >= i) {
                        for (int j = 0; j <= attacker.item2->radius; j++) {
                            UNIT defender;
                            if (peek_at(&armies[1], j, &defender)) {
                                int de = 0;
                                if (defender.item1) {
                                    de += defender.item1->def;
                                }
                                if (defender.item2) {
                                    de += defender.item2->def;
                                }
                                const int d = max(attacker.item2 -> att - de, 1);
                                armies[1].units[j].hp -= d;
                                dmg[dmg_count].army = 1;
                                strncpy(dmg[dmg_count].att_name, attacker.name, MAX_NAME);
                                dmg[dmg_count].att_name[MAX_NAME] = '\0';
                                strncpy(dmg[dmg_count].item, attacker.item2->name, MAX_NAME);
                                dmg[dmg_count].item[MAX_NAME] = '\0';
                                dmg[dmg_count].item_number = 2;
                                strncpy(dmg[dmg_count].def_name, defender.name, MAX_NAME);
                                dmg[dmg_count].def_name[MAX_NAME] = '\0';
                                dmg[dmg_count].dmg = d;
                                dmg_count++;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i <= armies[1].top; i++) {
            UNIT attacker;
            if (peek_at(&armies[1], i, &attacker)) {
                if (attacker.item1) {
                    if (attacker.item1->range >= i) {
                        for (int j = 0; j <= attacker.item1->radius; j++) {
                            UNIT defender;
                            if (peek_at(&armies[0], j, &defender)) {
                                int de = 0;
                                if (defender.item1) {
                                    de += defender.item1->def;
                                }
                                if (defender.item2) {
                                    de += defender.item2->def;
                                }
                                const int d = max(attacker.item1 -> att - de, 1);
                                armies[0].units[j].hp -= d;
                                dmg[dmg_count].army = 2;
                                strncpy(dmg[dmg_count].att_name, attacker.name, MAX_NAME);
                                dmg[dmg_count].att_name[MAX_NAME] = '\0';
                                strncpy(dmg[dmg_count].item, attacker.item1->name, MAX_NAME);
                                dmg[dmg_count].item[MAX_NAME] = '\0';
                                dmg[dmg_count].item_number = 1;
                                strncpy(dmg[dmg_count].def_name, defender.name, MAX_NAME);
                                dmg[dmg_count].def_name[MAX_NAME] = '\0';
                                dmg[dmg_count].dmg = d;
                                dmg_count++;
                            }
                        }
                    }
                }
                if (attacker.item2) {
                    if (attacker.item2 -> range >= i) {
                        for (int j = 0; j <= attacker.item2->radius; j++) {
                            UNIT defender;
                            if (peek_at(&armies[0], j, &defender)) {
                                int de = 0;
                                if (defender.item1) {
                                    de += defender.item1->def;
                                }
                                if (defender.item2) {
                                    de += defender.item2->def;
                                }
                                const int d = max(attacker.item2 -> att - de, 1);
                                armies[0].units[j].hp -= d;
                                dmg[dmg_count].army = 2;
                                strncpy(dmg[dmg_count].att_name, attacker.name, MAX_NAME);
                                dmg[dmg_count].att_name[MAX_NAME] = '\0';
                                strncpy(dmg[dmg_count].item, attacker.item2->name, MAX_NAME);
                                dmg[dmg_count].item[MAX_NAME] = '\0';
                                dmg[dmg_count].item_number = 2;
                                strncpy(dmg[dmg_count].def_name, defender.name, MAX_NAME);
                                dmg[dmg_count].def_name[MAX_NAME] = '\0';
                                dmg[dmg_count].dmg = d;
                                dmg_count++;
                            }
                        }
                    }
                }
            }
        }
        char *name = dmg[0].att_name;
        char *item = dmg[0].item;
        int number = dmg[0].item_number;
        printf("%d,%s,%s: [%s,%d] ", dmg[0].army, dmg[0].att_name, dmg[0].item, dmg[0].def_name, dmg[0].dmg);
        for (int i = 1; i < dmg_count; i++) {
            if ((strcasecmp(dmg[i].att_name, name) == 0) && (strcasecmp(dmg[i].item, item) == 0) && (dmg[i].item_number == number)) {
                printf("[%s,%d] ", dmg[i].def_name, dmg[i].dmg);
            } else {
                name = dmg[i].att_name;
                item = dmg[i].item;
                number = dmg[i].item_number;
                printf("\n%d,%s,%s: [%s,%d] ", dmg[i].army, dmg[i].att_name, dmg[i].item, dmg[i].def_name, dmg[i].dmg);
            }
        }
        printf("\n");
        for (int i = armies[0].top; i >= 0; i--) {
            if (armies[0].units[i].hp <= 0) {
                pop_at(&armies[0], i);
            }
        }
        for (int i = armies[1].top; i >= 0; i--) {
            if (armies[1].units[i].hp <= 0) {
                pop_at(&armies[1], i);
            }
        }
        printf("%d: ", 1);
        print_units(armies[0]);
        printf("%d: ", 2);
        print_units(armies[1]);
        round++;
        printf("\n");
    }

    if (max_rounds != 0) {
        if (armies[0].top == -1 && armies[1].top == -1) printf("NO WINNER\n");
        else if (armies[0].top == -1) printf("WINNER: 2\n");
        else if(armies[1].top == -1) printf("WINNER: 1\n");
    }
    return 1;
}
