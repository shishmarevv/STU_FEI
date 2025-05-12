#include <locale.h>
#include <stdio.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>


#define DEFAULT_BUFLEN 4096

void error(const char *msg) {
    fputs(msg, stderr);
    exit(1);
}

int compute_ID(const int ID) {
    int sum = (ID / 100000) % 10 + (ID / 10000) % 10 + (ID / 1000) % 10 + (ID / 100) % 10 + (ID / 10) % 10;
    sum = sum%((ID/10)%10);
    return sum;
}

void set_color(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
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
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int len = strlen(text);
    int max_len = get_console_width(hConsole) / 2;

    SHORT x = csbi.srWindow.Left;
    SHORT y = csbi.dwCursorPosition.Y;
    COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);

    for (int i = 0; i < len; i++) {
        char word[max_len];
        int j = 0;
        while (text[i] != ' ' && text[i] != '\0' && text[i] != '\n' && j < max_len - 1) {
            word[j] = text[i];
            i++;
            j++;
        }
        j++;
        word[j] = ' ';

        if ((i - j)%max_len + j < max_len) {
            custom_print(word, j, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        } else {
            coord.Y++;
            SetConsoleCursorPosition(hConsole, coord);
            custom_print(word, j, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        }
    }
    coord.Y++;
    SetConsoleCursorPosition(hConsole, coord);
}

void print_right(HANDLE hConsole, char *text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int len = strlen(text);
    int max_len = get_console_width(hConsole) / 2;

    SHORT x = csbi.srWindow.Left + max_len;
    SHORT y = csbi.dwCursorPosition.Y;

    COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);

    for (int i = 0; i < len; i++) {
        char word[max_len];
        int j = 0;
        while (text[i] != ' ' && text[i] != '\0' && j < max_len - 1) {
            word[j] = text[i];
            i++;
            j++;
        }
        j++;
        word[j] = ' ';

        if ((i - j)%max_len + j < max_len) {
            custom_print(word, j, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        } else {
            coord.Y++;
            SetConsoleCursorPosition(hConsole, coord);
            custom_print(word, j, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        }
    }
    coord.Y++;
    SetConsoleCursorPosition(hConsole, coord);
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

    printf("Sent %d bytes\n", iResult);
}

void my_get(SOCKET connect_socket, char *msg) {
    int iResult = recv(connect_socket, msg, DEFAULT_BUFLEN, 0);

    if (iResult > 0) {
        printf("Received %d bytes\n", iResult);
    } else if (iResult == 0) {
        error("Connection closed");
    } else {
        error("recv failed");
    }
}

int main() {
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(CP_UTF8);

    char buffer[DEFAULT_BUFLEN] = {0};

    SOCKET connect_socket = my_connect();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return 1;

    while (1) {
        memset(buffer, 0, DEFAULT_BUFLEN);
        print_right(hConsole, "Please enter the message: ");
        set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        fgets(buffer, DEFAULT_BUFLEN, stdin);

        if (strcmp(buffer, "exit\n") == 0) {
            print_left(hConsole, "Exiting and closing socket...\n");
            break;
        }
        if (strcmp(buffer, "compute id\nom") == 0) {
            int id = compute_ID(127855);
            char buff[15];
            sprintf(buff, "Result: %d\n", id);
            print_right(hConsole, buff);
            memset(buffer, 0, DEFAULT_BUFLEN);
            sprintf(buffer, "%d\n", id);
        }

        my_send(connect_socket, buffer);

        memset(buffer, 0, DEFAULT_BUFLEN);

        my_get(connect_socket, buffer);

        print_left(hConsole, buffer);
    }

    closesocket(connect_socket);
    print_left(hConsole, "Connection closed");
    return 0;
}