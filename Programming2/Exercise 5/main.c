#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "data.h"

typedef struct {
    ITEM *items;
    size_t count;
} ItemList;

typedef struct {
    struct unit units[5];
    int top;
} ARMY;

void initA(ARMY *s) {
    s->top = -1;
    for (int i = 0; i < 5; i++) {
        s->units[i].hp = 0;
        s->units[i].item1 = NULL;
        s->units[i].item2 = NULL;
        memset(s->units[i].name, 0, sizeof(s->units[i].name));
    }
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

void error(const char *msg) {
    printf("%s\n", msg);
    exit(0);
}

int skip(FILE *file) {
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (!isspace(c) && c != '\n') {
            return c;
        }
    }
}


void load_items(FILE *json, ItemList *item_list) {
    int c;

    while ((c = fgetc(json)) != EOF && c != '[') {}

    while ((c = fgetc(json)) != EOF && c != ']') {
        c = skip(json);
        if (c == '{') {
            ITEM item = {0};
            bool attributes[6] = {false};

            while ((c = fgetc(json)) != EOF && c != '}') {
                c = skip(json);
                if (c == '"') {
                    char key[MAX_NAME];
                    int i = 0;

                    while ((c = fgetc(json)) != EOF && c != '"' && i < MAX_NAME) {
                        key[i++] = (char) c;
                    }
                    key[i] = '\0';

                    c = skip(json);
                    if (c == ':') {
                        if (strcmp(key, "name") == 0) {
                            c = skip(json);
                            if (c == '"') {
                                i = 0;
                                while ((c = fgetc(json)) != EOF && c != '"' && i < MAX_NAME) {
                                    item.name[i++] = (char) c;
                                }
                                item.name[i] = '\0';
                                attributes[0] = true;
                            } else if (c == ',') {
                                error(ERR_MISSING_VALUE);
                            } else {
                                error(ERR_BAD_VALUE);
                            }
                        } else if (strcmp(key, "att") == 0) {
                            c = skip(json);
                            ungetc(c, json);
                            if (fscanf(json, "%d", &item.att) == 1) {
                                attributes[1] = true;
                            } else {
                                if (c == ',') {
                                    error(ERR_MISSING_VALUE);
                                } else {
                                    error(ERR_BAD_VALUE);
                                }
                            }
                        } else if (strcmp(key, "def") == 0) {
                            c = skip(json);
                            ungetc(c, json);
                            if (fscanf(json, "%d", &item.def) == 1) {
                                attributes[2] = true;
                            } else {
                                if (c == ',') {
                                    error(ERR_MISSING_VALUE);
                                } else {
                                    error(ERR_BAD_VALUE);
                                }
                            }
                        } else if (strcmp(key, "slots") == 0) {
                            c = skip(json);
                            ungetc(c, json);
                            if (fscanf(json, "%d", &item.slots) == 1) {
                                attributes[3] = true;
                            } else {
                                if (c == ',') {
                                    error(ERR_MISSING_VALUE);
                                } else {
                                    error(ERR_BAD_VALUE);
                                }
                            }
                        } else if (strcmp(key, "range") == 0) {
                            c = skip(json);
                            ungetc(c, json);
                            if (fscanf(json, "%d", &item.range) == 1) {
                                attributes[4] = true;
                            } else {
                                if (c == ',') {
                                    error(ERR_MISSING_VALUE);
                                } else {
                                    error(ERR_BAD_VALUE);
                                }
                            }
                        } else if (strcmp(key, "radius") == 0) {
                            c = skip(json);
                            ungetc(c, json);
                            if (fscanf(json, "%d", &item.radius) == 1) {
                                attributes[5] = true;
                            } else {
                                if (c == ',') {
                                    error(ERR_MISSING_VALUE);
                                } else {
                                    error(ERR_BAD_VALUE);
                                }
                            }
                        }
                    }
                }
            }

            if (attributes[0] && attributes[1] && attributes[2] && attributes[3] && attributes[4] && attributes[5]) {
                item_list->items[item_list->count++] = item;
            } else {
                error(ERR_MISSING_ATTRIBUTE);
            }
        }
    }
}

const ITEM* find(const char* name, const ItemList *item_list) {
    for(int i=0; i< item_list -> count; i++) {
        if(strcasecmp(item_list->items[i].name, name) == 0) return &(item_list->items[i]);
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

void load_army(FILE *txt, const ItemList *item_list, ARMY *army) {
    initA(army);
    int unit_count;
    if (fscanf(txt, "%d", &unit_count) != 1 || unit_count < MIN_ARMY || unit_count > MAX_ARMY) {
        error(ERR_UNIT_COUNT);
    }
    getchar();
    for(int i = 0; i < unit_count; i++) {
        UNIT u = {.hp = 100, .item2 = NULL};
        char name[MAX_NAME + 1] = {0};
        char item1[MAX_NAME + 1] = {0};
        char item2[MAX_NAME + 1] = {0};

        char c;
        int items_read = 0, j = 0;
        while ((c = (char) getchar()) != '\n' && c != EOF) {
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

                }
            }
        }
        items_read++;

        if (items_read < 2) {
            error("ERR_ITEM_COUNT");
        }

        strncpy(u.name, name, MAX_NAME);

        const ITEM* it = find(item1, item_list);
        if(!it) {
            error(ERR_WRONG_ITEM);
        }
        u.item1 = it;

        if(items_read > 2 && strlen(item2) > 0) {
            it = find(item2, item_list);
            if(!it) {
                error(ERR_WRONG_ITEM);
            }
            u.item2 = it;
        }

        if(!check_slots(u)) {
            error(ERR_SLOTS);
        }

        if(!push(army, u)) {
            error(ERR_UNIT_COUNT);
        }
    }
}

void print_items(const ItemList *item_list) {
    for (int i = 0; i < item_list->count; i++) {
        printf("Name: %s\n", item_list->items[i].name);
        printf("Attack: %d\n", item_list->items[i].att);
        printf("Defense: %d\n", item_list->items[i].def);
        printf("Slots: %d\n", item_list->items[i].slots);
        printf("Range: %d\n", item_list->items[i].range);
        printf("Radius: %d\n", item_list->items[i].radius);
        printf("\n");
    }
}



int main(const int argc, char *argv[]){
    if (argc == 1) {
        FILE *json = fopen(ITEMS_FILE, "r");
        if (json == NULL) {
            error(ERR_FILE);
        }
        ItemList item_list;
        item_list.items = malloc(sizeof(ITEM) * MAX_ARMY);
        load_items(json, &item_list);
        fclose(json);
        print_items(&item_list);
        free(item_list.items);
    } else if (argc == 2) {
        FILE *json = fopen(ITEMS_FILE, "r");
        if (json == NULL) {
            error(ERR_FILE);
        }
        ItemList item_list;
        item_list.items = malloc(sizeof(ITEM) * MAX_ARMY);
        load_items(json, &item_list);
        fclose(json);

        ARMY armies[2];
        FILE *txt = fopen(argv[1], "r");
        if (txt == NULL) {
            error(ERR_FILE);
        }
        load_army(txt, &item_list, &armies[0]);
        fclose(txt);
        txt = fopen(argv[2], "r");
        load_army(txt, &item_list, &armies[1]);
        fclose(txt);
        print_army(armies[0], 1);
        print_army(armies[1], 2);
    } else {
        error(ERR_CMD);
    }
    return 1;
}
