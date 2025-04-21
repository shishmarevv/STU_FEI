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
    char def_name[MAX_NAME + 1];
    int dmg;
} DAMAGE;

void init(ARMY *s) {
    s->top = -1;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void error (const char *msg) {
    printf("%s\n", msg);
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


bool pop_at(ARMY *s, int index, UNIT *out) {
    if (index < 0 || index > s->top) return false;

    *out = s->units[index];

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

void print_army(ARMY* a, int num) {
    printf("Army %d\n", num);
    for(int i=-1; i<a->top; i++) {
        printf("Unit: %d\nName: %s\nHP: %d\n", i, a->units[i].name, a->units[i].hp);
        if(a->units[i].item1) {
            printf("Item %d: %s,%d,%d,%d,%d,%d\n", 1,
                a->units[i].item1->name,
                a->units[i].item1->att,
                a->units[i].item1->def,
                a->units[i].item1->slots,
                a->units[i].item1->range,
                a->units[i].item1->radius);
        }
        if(a->units[i].item2) {
            printf("Item %d: %s,%d,%d,%d,%d,%d\n", 2,
                a->units[i].item2->name,
                a->units[i].item2->att,
                a->units[i].item2->def,
                a->units[i].item2->slots,
                a->units[i].item2->range,
                a->units[i].item2->radius);
        }
        printf("\n");
    }
}

const ITEM* find(const char* name) {
    for(int i=0; i<NUMBER_OF_ITEMS; i++) {
        if(strcasecmp(items[i].name, name) == 0) return &items[i];
    }
    return NULL;
}

bool check_slots(UNIT* un) {
    if (un->item1->slots + un->item2->slots > 2) {
        return false;
    }
    return true;
}


int main(const int argc, char *argv[]) {
    ARMY armies[2] = {0};
    init(&armies[0]);
    init(&armies[1]);
    int max_rounds = (argc > 1) ? atoi(argv[1]) : -1;

    for(int army_num=0; army_num<2; army_num++) {
        int unit_count;
        scanf("%d", &unit_count);
        if(unit_count <1 || unit_count>5) {
            error(ERR_UNIT_COUNT);
            return 0;
        }
        armies[army_num].top = unit_count - 1;

        for(int i=0; i<unit_count; i++) {
            UNIT u = {.hp = 100};
            char name[MAX_NAME], item1[MAX_NAME], item2[MAX_NAME];
            scanf("%s %s %s", name, item1, item2);
            strncpy(u.name, name, MAX_NAME);

            const ITEM* it = find(item1);
            if(!it) {
                printf("ERR_WRONG_ITEM\n");
                return 0;
            }
            u.item1 = it;

            if(strcmp(item2, "-") != 0) {
                it = find(item2);
                if(!it) {
                    printf("ERR_WRONG_ITEM\n");
                    return 0;
                }
                u.item2 = it;
            }

            if(!check_slots(&u)) {
                printf("ERR_SLOTS\n");
                return 0;
            }
            if(!push(&armies[army_num], u)) {
                printf("ERR_UNIT_COUNT\n");
                return 0;
            }
        }
    }



    int round = 0;
    while((max_rounds == -1 || round < max_rounds) && armies[0].top > -1 && armies[1].top > -1) {
        print_army(&armies[0], 1);
        print_army(&armies[1], 2);
        DAMAGE dmg[20] = {0};
        int dmg_count = 0;
        for (int i = 0; i <= armies[0].top; i++) {
            UNIT attacker;
            if (peek_at(&armies[0], i, &attacker)) {
                if (attacker.item1) {
                    if (attacker.item1->range >= i) {
                        for (int j = 0; j <= attacker.item1->radius; j++) {
                            UNIT defender;
                            if (peek_at(&armies[1], j, &defender)) {
                                int def = 0;
                                if (defender.item1) {
                                    def += defender.item1->def;
                                }
                                if (defender.item2) {
                                    def += defender.item2->def;
                                }
                                const int d = max(attacker.item1 -> att - def, 1);
                                armies[1].units[j].hp -= d;
                                dmg[dmg_count] = (DAMAGE) {
                                    .army = 1,
                                    .att_name = attacker.name,
                                    .item = attacker.item1->name,
                                    .def_name = defender.name,
                                    .dmg = d
                                };
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
                                int def = 1;
                                if (defender.item1) {
                                    def += defender.item1->def;
                                }
                                if (defender.item2) {
                                    def += defender.item2->def;
                                }
                                const int d = max(attacker.item2 -> att - def, 1);
                                armies[1].units[j].hp -= d;
                                dmg[dmg_count] = (DAMAGE) {
                                    .army = 1,
                                    .att_name = attacker.name,
                                    .item = attacker.item2->name,
                                    .def_name = defender.name,
                                    .dmg = d
                                };
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
                                int def = 0;
                                if (defender.item1) {
                                    def += defender.item1->def;
                                }
                                if (defender.item2) {
                                    def += defender.item2->def;
                                }
                                const int d = max(attacker.item1 -> att - def, 1);
                                armies[0].units[j].hp -= d;
                                dmg[dmg_count] = (DAMAGE) {
                                    .army = 2,
                                    .att_name = attacker.name,
                                    .item = attacker.item1->name,
                                    .def_name = defender.name,
                                    .dmg = d
                                };
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
                                int def = 0;
                                if (defender.item1) {
                                    def += defender.item1->def;
                                }
                                if (defender.item2) {
                                    def += defender.item2->def;
                                }
                                const int d = max(attacker.item2 -> att - def, 1);
                                armies[0].units[j].hp -= d;
                                dmg[dmg_count] = (DAMAGE) {
                                    .army = 2,
                                    .att_name = attacker.name,
                                    .item = attacker.item2->name,
                                    .def_name = defender.name,
                                    .dmg = d
                                };
                                dmg_count++;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < dmg_count; i++) {
            printf("%d,%s,%s: [%s,%d]\n", dmg[i].army, dmg[i].att_name, dmg[i].item, dmg[i].def_name, dmg[i].dmg);
        }
        for (int i = 0; i <= armies[0].top; i++) {
            if (armies[0].units[i].hp <= 0) {
                pop_at(&armies[0], i, NULL);
                i--;
            }
        }
        for (int i = 0; i <= armies[1].top; i++) {
            if (armies[1].units[i].hp <= 0) {
                pop_at(&armies[1], i, NULL);
                i--;
            }
        }
        print_army(&armies[0], 1);
        print_army(&armies[1], 2);
        round++;
    }

    if(armies[0].top == -1) printf("WINNER 2\n");
    else if(armies[1].top == -1) printf("WINNER 1\n");
    else printf("NO WINNER\n");

    return 0;
}
