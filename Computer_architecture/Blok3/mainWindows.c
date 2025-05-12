#include <locale.h>
#include <stdio.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <math.h>

#define DEFAULT_BUFLEN 4096

void set_color(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void error(const char *msg) {
    fputs(msg, stderr);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    exit(1);
}

int compute_ID(const int ID) {
    int sum = (ID / 100000) % 10 + (ID / 10000) % 10 + (ID / 1000) % 10 + (ID / 100) % 10 + (ID / 10) % 10;
    sum = sum%((ID/10)%10);
    return sum;
}

void custom_print(char *buffer, int len, WORD color){
    buffer[len] = '\0';
    for (int i = 0; i < len; i++){
        set_color(color);
        printf("%c", buffer[i]);
        set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        fflush(stdout);
        usleep(15000);
    }
}

int get_console_width(HANDLE hConsole) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return 80;
    }
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void print_left(HANDLE hConsole, char *text) {
    int len = strlen(text);
    int max_len = get_console_width(hConsole) / 2;

    int symbols_in_line = 0;

    for (int i = 0; i < len; i++) {
        char word[max_len];
        memset(word, 0, max_len);
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
            custom_print(word, j, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        } else {
            symbols_in_line = j;
            printf("\n");
            custom_print(word, j, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        }
    }
    printf("\n");
}

void print_right(HANDLE hConsole, char *text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int len = strlen(text);
    int max_len = get_console_width(hConsole) / 2;

    SHORT x = csbi.srWindow.Left + max_len + 1;
    SHORT y = csbi.dwCursorPosition.Y;
    COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);

    int symbols_in_line = 0;

    for (int i = 0; i < len; i++) {
        char word[max_len];
        memset(word, 0, max_len);
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
            custom_print(word, j, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        } else {
            symbols_in_line = j;
            coord.X = csbi.srWindow.Left + max_len + 1;
            coord.Y++;
            SetConsoleCursorPosition(hConsole, coord);
            if (csbi.dwCursorPosition.Y >= csbi.srWindow.Bottom) {
                putchar('\n');
                GetConsoleScreenBufferInfo(hConsole, &csbi);
                coord.X = csbi.srWindow.Left + max_len + 1;
                coord.Y = csbi.dwCursorPosition.Y;
                SetConsoleCursorPosition(hConsole, coord);
            }
            custom_print(word, j, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        }
    }
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    coord.Y = csbi.dwCursorPosition.Y;
    coord.X = csbi.srWindow.Left;
    SetConsoleCursorPosition(hConsole, coord);
    putchar('\n');
}


void decipher(char *in, const int key, const int length) {
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    for (int i = 0; i < length; i++) {
        if (in[i] != ' ' && in[i] != '\0' && in[i] != '\n') {
            putchar(in[i]);
        }
        in[i] ^= key;
    }
    putchar('\n');
}

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void prime(char *in, char *out) {
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

SOCKET my_connect() {
    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        error("WSAStartup failed");
    }

    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("147.175.115.34", "777", &hints, &result);
    if (iResult != 0) {
        WSACleanup();
        error("getaddrinfo failed");
    }

    SOCKET connect_socket = INVALID_SOCKET;

    ptr = result;

    connect_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (connect_socket == INVALID_SOCKET) {
        freeaddrinfo(result);
        WSACleanup();
        error("socket failed");
    }

    iResult = connect(connect_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(connect_socket);
        connect_socket = INVALID_SOCKET;
        WSACleanup();
        error("connect failed");
    }
    return connect_socket;

    sleep(250);
}

void my_send(SOCKET connect_socket, char *msg) {
    int iResult = send(connect_socket, msg, (int) strlen(msg), 0);

    if (iResult == SOCKET_ERROR) {
        closesocket(connect_socket);
        WSACleanup();
        error("send failed");
    }

}

void my_get(SOCKET connect_socket, char *msg) {
    int iResult = recv(connect_socket, msg, DEFAULT_BUFLEN, 0);

    if (iResult == 0) {
        error("Connection closed");
    } else if (iResult < 0) {
        error("recv failed");
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    char buffer[DEFAULT_BUFLEN] = {0};
    char old_buffer[DEFAULT_BUFLEN] = {0};

    SOCKET connect_socket = my_connect();

    FILE *file = fopen("log.txt", "w");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return 1;

    while (1) {
        memset(buffer, 0, DEFAULT_BUFLEN);
        print_left(hConsole, "Please enter the message: ");
        set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        fgets(buffer, DEFAULT_BUFLEN, stdin);

        if (strcmp(buffer, "exit\n") == 0) {
            print_right(hConsole, "Exiting and closing socket...\n");
            logger(file, "Exiting and closing socket...\n", strlen("Exiting and closing socket...\n"));
            set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        }
        if (strcmp(buffer, "compute id\n") == 0) {
            int id = compute_ID(127855);
            char buff[15];
            sprintf(buffer, "%d\n", id);
        }
        if (strcmp(buffer, "decipher\n") == 0) {
            decipher(old_buffer, 55, 132);
            print_right(hConsole, old_buffer);
            logger(file, old_buffer, strlen(old_buffer));
            continue;
        }
        if (strcmp(buffer, "prime\n") == 0) {
            memset(buffer, 0, DEFAULT_BUFLEN);
            prime(old_buffer, buffer);
        }

        my_send(connect_socket, buffer);
        logger(file, buffer, DEFAULT_BUFLEN);

        memset(buffer, 0, DEFAULT_BUFLEN);

        my_get(connect_socket, buffer);
        logger(file, buffer, DEFAULT_BUFLEN);
        memcpy(old_buffer, buffer, DEFAULT_BUFLEN);

        print_right(hConsole, buffer);
    }

    fclose(file);
    closesocket(connect_socket);
    print_right(hConsole, "Connection closed");
    return 0;
}