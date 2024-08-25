#include <stdio.h>
#include <winsock2.h>

#define HOST "127.0.0.1"
#define PORT 8080
#define LENGTH_CHAR 255
#define VALUE_ASCII 48

void configClientSocket(WSADATA *wsa, SOCKET *client_socket, struct sockaddr_in *server) {

    WSAStartup(MAKEWORD(2,2), wsa);

    *client_socket = socket(AF_INET, SOCK_STREAM, 0);

    server->sin_family = AF_INET;
    server->sin_port = htons(PORT);
    server->sin_addr.s_addr = inet_addr(HOST);
}

void deleteLineBreak(char *string) {
	size_t len = strlen(string);

    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }
}

void addLineBreak() {
    printf("\n");
}

void clearConsole() {
	system("cls");
}

void mainMenu(char *option) {

    int optionSwitch;

    do {
        addLineBreak();
        printf("*** 1- GENERAR NOMBRE DE USUARIO ***");
        addLineBreak();
        printf("*** 2- GENERAR CLAVE DE USUARIO ***");
        addLineBreak();
        printf("*** 3- SALIR DEL PROGRAMA ***");
        addLineBreak();
        printf("ELIJA UNA OPCION: ");

        scanf("%s", option);

        optionSwitch = (int) option[0] - VALUE_ASCII;

        switch(optionSwitch) {
            case 1:
            case 2:
            case 3: optionSwitch = 3; break;
            default:
                clearConsole();
                printf("OPCION INCORRECTA, ELIJA DE NUEVO POR FAVOR: ");
        }

    } while(optionSwitch != 3);

}

int main() {

    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;

    char message[LENGTH_CHAR];
    char response[LENGTH_CHAR];
    char option[] = "0";
    int closeProgram;

    configClientSocket(&wsa, &client_socket, &server);

    connect(client_socket, (struct sockaddr*)&server, sizeof(server));

    mainMenu(option);
    closeProgram = (int) option[0] - VALUE_ASCII;

    strcpy(message, option);
    send(client_socket, message, strlen(message), 0);

    memset(response, 0, sizeof(response));

    //Recibe el mensaje
    recv(client_socket, response, LENGTH_CHAR, 0);
    deleteLineBreak(response);

    addLineBreak();

    if(closeProgram == 3) {
        printf_s("%s", response);
    }

    else {
        printf_s("%s ", response);
        scanf("%s", message);

        send(client_socket, message, strlen(message), 0);

        ////////////////////////////////////
        memset(response, 0, sizeof(response));

        recv(client_socket, response, LENGTH_CHAR, 0);

        addLineBreak();

        printf_s("%s", response);
        ////////////////////////////////////

        addLineBreak();
    }

    closesocket(client_socket);
    WSACleanup();

    return 0;
}
