#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <locale.h>
#include <ncurses.h>
#include <math.h>

#define DEFAULT_BUFLEN 4096
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

void error(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

int get_term_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void custom_print(char *buffer, int len, char *color){
    setlocale(LC_ALL, "");
    buffer[len] = '\0';
    for (int i = 0; i < len; i++){
        printf("%s%c%s", color, buffer[i], RESET);
        fflush(stdout);
        usleep(15000);
    }
}

void print_left(char *text) {
    int len = strlen(text);
    int max_len = get_term_width() / 2;

    int symbols_in_line = 0;

    for (int i = 0; i < len; i++) {
        char word[max_len];
        bzero(word, len);
        int j = 0;
        while (text[i] != ' ' && text[i] != '\0' && text[i] != '\n' && j < max_len - 1) {
            word[j] = text[i];
            i++;
            j++;
        }
        word[j] = ' ';
        j++;

        if (symbols_in_line + j <= max_len) {
            symbols_in_line += j;
            custom_print(word, j, BLUE);
        } else {
            symbols_in_line = j;
            printf("\n");
            custom_print(word, j, BLUE);
        }
    }
    printf("\n");
}


void print_right(char *text) {
    int max_len, len = strlen(text);
    int cur_x, cur_y, start_x;
    int symbols_in_line = 0;

    initscr();

    max_len = get_term_width() / 2;

    getyx(stdscr, cur_y, cur_x);
    start_x = max_len + 1;

    move(cur_y, start_x);

    for (int i = 0; i < len; i++) {
        char word[max_len];
        bzero(word, len);
        int j = 0;
        while (text[i] != ' ' && text[i] != '\0' && text[i] != '\n' && j < max_len - 1) {
            word[j] = text[i];
            i++;
            j++;
        }
        word[j] = ' ';
        j++;

        if (symbols_in_line + j <= max_len) {
            symbols_in_line += j;
            custom_print(word, j, GREEN);
        } else {
            symbols_in_line = j;
            cur_y++;
            move(cur_y, start_x);
            custom_print(word, j, GREEN);
        }
    }

    getyx(stdscr, cur_y, cur_x);
    move(cur_y + 1, 0);
    refresh();
    endwin();
}

int calc(int ID){
    int sum;
    sum = (ID/100000)%10 + (ID/10000)%10 + (ID/1000)%10 + (ID/100)%10 + (ID/10)%10;
    sum = sum%((ID/10)%10);
    return sum;
}

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i <= (int) sqrt((double) n); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void prime_decipher(char *in, char *out) {
    int j = 0;
    for (int i = 0; i < DEFAULT_BUFLEN; i++) {
        if (is_prime(i + 1)) {
            out[j] = in[i];
            j++;
        }
    }
}

void logger(FILE *file, char *msg, int len) {
    for (int i = 0; i < len; i++) {
        if (msg[i] == '\0') continue;
        fputc(msg[i], file);
    }
    fputc('\n', file);
}

void decrypt(char *in, const int key, const int length) {
    for (int i = 0; i < length; i++) {
        in[i] ^= key;
        putchar(in[i]);
    }
    putchar('\n');
}

int connection(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[DEFAULT_BUFLEN];

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\nUsing default values\n", argv[0]);
        portno = 777;
        server = gethostbyname("147.175.115.34");
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
    } else {
        portno = atoi(argv[2]);
        server = gethostbyname(argv[1]);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");


    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  // Use IPv4

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");

    return sockfd;
}

void message(int sockfd, char *msg) {
    const int n = (int) write(sockfd, msg, DEFAULT_BUFLEN);
    if (n < 0) error("ERROR writing to socket");
    bzero(msg, DEFAULT_BUFLEN);
}

void get(int sockfd, char *msg) {
    bzero(msg, DEFAULT_BUFLEN);
    const int n = (int) read(sockfd, msg, DEFAULT_BUFLEN);
    if (n < 0) error("ERROR reading from socket");
}


int main(int argc, char *argv[]){
    char buffer[DEFAULT_BUFLEN] = {0};
    char cash[DEFAULT_BUFLEN] = {0};

    FILE *file = fopen("log.txt", "w");
    if (file == NULL) error("ERROR opening file");

    int sockfd = connection(argc, argv);

    while (1) {
        bzero(buffer, DEFAULT_BUFLEN);
        print_left("Enter the message: ");
        printf("%s\n", BLUE);
        fgets(buffer, DEFAULT_BUFLEN, stdin);

        if (strcmp(buffer, "quit\n") == 0) {
            print_right( "Exiting and closing socket...\n");
            logger(file, "Exiting and closing socket...\n", strlen("Exiting and closing socket...\n"));
            break;
        }
        if (strcmp(buffer, "id\n") == 0) {
            int id = 127855;
            sprintf(buffer, "%d\n", id);
        }
        if (strcmp(buffer, "calc\n") == 0) {
            int res = calc(127855);
            sprintf(buffer, "%d\n", res);
        }
        if (strcmp(buffer, "decrypt\n") == 0) {
            decrypt(cash, 55, 132);
            print_right(cash);
            logger(file, cash, DEFAULT_BUFLEN);
            continue;
        }
        if (strcmp(buffer, "prime decrypt\n") == 0) {
            bzero(buffer, DEFAULT_BUFLEN);
            prime_decipher(cash, buffer);
        }

        message(sockfd, buffer);
        logger(file, buffer, DEFAULT_BUFLEN);

        get(sockfd, buffer);
        logger(file, buffer, DEFAULT_BUFLEN);
        memcpy(cash, buffer, DEFAULT_BUFLEN);

        print_right(buffer);
    }

    fclose(file);
    close(sockfd);
    print_right("Connection closed\n");
    return 0;
}