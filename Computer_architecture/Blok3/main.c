#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <locale.h>

#define DEFAULT_BUFLEN 4096
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

// Print an error message (using perror) and exit the program
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int get_term_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int calc(int ID){
    int sum;
    sum = (ID/100000)%10 + (ID/10000)%10 + (ID/1000)%10 + (ID/100)%10 + (ID/10)%10;
    sum = sum%((ID/10)%10);
    return sum;
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

void print_block(const char *text, int align_left) {
    int len = strlen(text);
    int half = get_term_width() / 2;
    int pad = 0;
    char *color = GREEN;
    if (align_left) {
        color = BLUE;
        pad = half;
        printf("%*s", pad, "");
    }
    for (int i = 0; i < len; i++) {
        char word[100];
        int j = 0;
        while (!isspace(text[i]) && text[i] != '\0' && text[i] != '\n') {
            word[j] = text[i];
            i++;
            j++;
        }
        word[j] = ' ';
        if ((i - j)%half + j < half) {
            custom_print(word, j, color);
        } else {
            printf("\n%*s", pad, "");
            custom_print(word, j, color);
        }
    }
    printf("\n");
}



int connection(int argc, char *argv[]) {

    // Inital settings

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[DEFAULT_BUFLEN];

    // Check that hostname and port number are provided
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\nUsing default values\n", argv[0]);
       //Default
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

    // Create a TCP socket (IPv4, stream-oriented)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    // Connecting to server

    // Zero out the server address structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  // Use IPv4

    // Copy the resolved IP address into the serv_addr struct
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    // Convert port number to network byte order and store it
    serv_addr.sin_port = htons(portno);

    // Establish a connection to the server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");

    while (1) {
        // Prompt the user to enter a messag
        sprintf(buffer,"%sPlease enter the message: ", BLUE);
        print_block(buffer, 1);
        bzero(buffer,DEFAULT_BUFLEN);
        fgets(buffer,DEFAULT_BUFLEN - 1,stdin);

        //Exit
        if (strcmp(buffer, "exit\n") == 0) {
            print_block("Exiting and closing socket...\n", 1);
            break;
        }
        if (strcmp(buffer, "compute id\nom") == 0) {
            int id = calc(127855);
            char buff[15];
            sprintf(buff, "Result: %d\n", id);
            print_block(buff, 1);
            sprintf(buffer, "%d\n", id);
        }

        // Send the message to the server
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0)
             error("ERROR writing to socket");

        // Clear the buffer and read the server's response
        bzero(buffer,DEFAULT_BUFLEN);
        n = read(sockfd,buffer, DEFAULT_BUFLEN - 1);
        if (n < 0)
             error("ERROR reading from socket");

        // Print the response from the server
        print_block(buffer, 0);
    }

    // Close the socket and exit

    printf("%s", RESET);
    close(sockfd);
    return 0;
}

int main(int argc, char *argv[]){
    connection(argc, argv);

    return 0;
}