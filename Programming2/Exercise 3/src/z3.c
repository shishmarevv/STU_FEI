#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100
#define ERR_OVERFLOW "ERR_OVERFLOW\n"
#define ERR_POSITION "ERR_POSITION\n"
#define ERR_OUT_OF_RANGE "ERR_OUT_OF_RANGE\n"

char op[LEN+1];
char mem[LEN+1];
char *sp, *ep;

const char *readline(){
     static char buf[256];
     fgets(buf, 256, stdin);
     buf[strcspn(buf, "\n")] = '\0';
     return buf;
}

void slice (char *src, char *dst, int start, int end) {
     for (int i = start; i < end; i++) {
          dst[i - start] = src[i];
     }
}

void error (const char *msg) {
     printf("%s\n", msg);
     exit(0);
}

void in (const char *input) {
     const unsigned int len = strlen(input);
     if (len > LEN) {
          error(ERR_OVERFLOW);
     }
     strcpy(op, input);
     sp = op;
     ep = op + len;
}

void out_op () {
     printf("%s\n", op);
}

void out_range () {
     if (sp > ep) error(ERR_POSITION);
     const unsigned len = ep - sp;
     for (int i = 0; i < len; i++) {
          putchar(sp[i]);
     }
     putchar('\n');
}

void out_mem() {
     printf("%s\n", mem);
}

void move (char **p, int n) {
     char *newp = *p + n;
     if (newp < op || newp > op + strlen(op)) {
          error(ERR_OUT_OF_RANGE);
     }
     *p = newp;
}

void strt(char **p) {
     *p = op;
}

void end(char **p) {
     *p = op + strlen(op);
}

void del() {
    if (sp > ep) error(ERR_POSITION);
    const int dlen = ep - sp;
    const int rem = strlen(op) - (sp - op) - dlen;
    memmove(sp, ep, rem + 1);
    ep = sp;
}

void crop() {
    if (sp > ep) error(ERR_POSITION);
    const int len = ep - sp;
    char temp[LEN+1];
    strncpy(temp, sp, len);
    temp[len] = '\0';
    strcpy(op, temp);
    sp = op;
    ep = op + len;
}

void copy() {
    if (sp > ep) error(ERR_POSITION);
    int len = ep - sp;
    if (len == 0) return;
    strncpy(mem, sp, len);
    mem[len] = '\0';
}


void insert(const char *param) {
    int curr = strlen(op);
    if (strcmp(param, "mem") == 0) {
        const int size = strlen(mem);
        if (size == 0) return;
        if (curr + size > LEN) error(ERR_OVERFLOW);
        const int set = sp - op;
        memmove(op + set + size, op + set, curr - set + 1);
        memcpy(op + set, mem, size);
        ep += size;
    } else {
        const int n = atoi(param);
        if (n <= 0) return;
        if (curr + n > LEN) error(ERR_OVERFLOW);
        const int set = sp - op;
        memmove(op + set + n, op + set, curr - set + 1);
        for (int i = 0; i < n; i++) {
            op[set + i] = ' ';
        }
        ep += n;
    }
}

void replace() {
    if (sp > ep) error(ERR_POSITION);
    if (strcmp(mem, "") == 0) return;
    const int len = ep - sp;
    const int newl = strlen(mem);
    const int set = sp - op;
    if (newl > len) {
         char slc[len];
         slice(mem, slc, 0, len);
         memcpy(op + set, slc, len);
         ep = sp + len;
    } else {
         memcpy(op + set, mem, newl);
         ep = sp + newl;
    }
}

int is(const char c) {
     if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
          return 1;
     } else {
          return 0;
     }
}

void first() {
     char *point = op;

     while (*point && !is(*point)) {
          if (*point == '\0') {
               sp = op;
               ep = op;
               return;
          }
          point++;
     }
     sp = point;
     while (*point && is(*point)) {
          point++;
     }
     ep = point;
}

void last() {
     char *point = op;
     char *last_start = NULL;
     char *last_end = NULL;
     char *start = NULL;

     unsigned int swtch = 0;

     while (*point != '\0') {

          if (is(*point) && swtch == 0) {
               start = point;
               swtch = 1;
          }
          if (!is(*point) && swtch == 1) {
               last_start = start;
               last_end = point;
               swtch = 0;
          }
          point++;
     }

     if (last_start == NULL) {
          sp = op + strlen(op);
          ep = sp;
     } else {
          sp = last_start;
          ep = last_end;
     }
}

void prev() {
     char *point;

     if (sp != op) {
          point = sp;
     } else {
          sp = op;
          ep = op;
          return;
     }


     while (point >= op && is(*point)) {
          point--;
     }

     while (point >= op && !is(*point)) {
          point--;
     }

     if (point < op) {
          sp = op;
          ep = op;
          return;
     }

     char *word_end = point + 1;

     while (point > op && is(*(point - 1))) {
          point--;
     }

     sp = point;
     ep = word_end;
}

void next() {
     char *point = sp;

     if (is((*point))) {
          while (is(*point)) {
               point++;
          }
     }

     while (!is(*point) && *point != '\0') {
          point++;
     }

     if (*point == '\0') {
          sp = op + strlen(op);
          ep = sp;
          return;
     }

     sp = point;

     while (is(*point)) {
          point++;
     }
     ep = point;
}

int main(){
     op[0] = '\0';
     mem[0] = '\0';
     sp = op;
     ep = op;
     while(1) {
          const char *input = readline();
          if (strcmp(input, "quit") == 0) {
               return 0;
          }
          if (strncmp(input, "in ", 3) == 0) {
               in(input + 3);
          } else if (strcmp(input, "out op") == 0) {
               out_op();
          } else if (strcmp(input, "out range") == 0) {
               out_range();
          } else if (strcmp(input, "out mem") == 0) {
               out_mem();
          } else if (strncmp(input, "move sp ", 8) == 0) {
               int n;
               if (sscanf(input + 8, "%d", &n) == 1) {
                    move(&sp, n);
               }
          } else if (strncmp(input, "move ep ", 8) == 0) {
               int n;
               if (sscanf(input + 8, "%d", &n) == 1) {
                    move(&ep, n);
               }
          } else if (strcmp(input, "start sp") == 0) {
               strt(&sp);
          } else if (strcmp(input, "start ep") == 0) {
               strt(&ep);
          } else if (strcmp(input, "end sp") == 0) {
               end(&sp);
          } else if (strcmp(input, "end ep") == 0) {
               end(&ep);
          } else if (strcmp(input, "del") == 0) {
               del();
          } else if (strcmp(input, "crop") == 0) {
               crop();
          } else if (strcmp(input, "copy") == 0) {
               copy();
          } else if (strncmp(input, "insert ", 7) == 0) {
              insert(input + 7);
          } else if (strcmp(input, "replace") == 0) {
               replace();
          } else if (strcmp(input, "first") == 0) {
               first();
          } else if (strcmp(input, "last") == 0) {
               last();
          } else if (strcmp(input, "prev") == 0) {
               prev();
          } else if (strcmp(input, "next") == 0) {
               next();
          }
     }

     return 1;
}