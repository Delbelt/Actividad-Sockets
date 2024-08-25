#include <stdio.h>
#include <winsock2.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define PORT 8080
#define LENGTH_CHAR 255
#define VALUE_ASCII 48

void configServerSocket(WSADATA *wsa, SOCKET *server_socket, struct sockaddr_in *server) {
	
	WSAStartup(MAKEWORD(2,2), wsa); 
    *server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server->sin_family = AF_INET;
    server->sin_addr.s_addr = INADDR_ANY;
    server->sin_port = htons(PORT);
    
    bind(*server_socket, (struct sockaddr*)server, sizeof(*server));   
}

bool isNumber(char *string) {
	return isdigit(string[0]);
}

void deleteLineBreak(char *string) {
	size_t len = strlen(string);
	
    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }
}

void generateUserName(int length, char *saveName) {
	
	int i;
	char userName[length];
	char lettersConsonant[] = "BCDFGHJKLMNPQRSTVWXYZ";
	char lettersVowels[] = "AEIOU";
	
	srand(time(NULL));
	
	int minConsonant = 0;
	int maxConsonant = 20;
	
	int minVowels = 0;
	int maxVowels = 4;
	
	int consonantOrVowels = rand() % 2; // 0 = Consonant | 1 = Vowels
	int randomLetter;

	for(i = 0; i < length; i++) {
		
		if(consonantOrVowels == 0) {
			randomLetter = rand() % (maxConsonant - minConsonant + 1) + minConsonant;
			userName[i] = lettersConsonant[randomLetter];
			consonantOrVowels = 1;
		}
			
		else {
			randomLetter = rand() % (maxVowels - minVowels + 1) + minVowels;
			userName[i] = lettersVowels[randomLetter];
			consonantOrVowels = 0;
		}	
	
	}
	
	deleteLineBreak(userName);
	
	strcpy(saveName, userName);
}

void generatePassword(int length, char *savePassword) {
	
	int i;
	char password[length];
	char alfanumeric[] = "UpjLastRgFYKwyJ25miHrhWMSlecv3fEoCVADbuQT67kxBzd1nNI9Oq4PG8XZ";
	
	int min = 0;
	int max = 60;
	int randomCharacter;
	
	srand(time(NULL));
	
		for(i = 0; i < length; i++) {
			randomCharacter = rand() % (max - min + 1) + min;
			password[i] = alfanumeric[randomCharacter];
		}
		
	deleteLineBreak(password);	
	strcpy(savePassword, password);
	
}

void processMessageGeneratorUsername(char *buffer, char *response) {
	if(isNumber(buffer)) {
	
	int length = atoi(buffer);
	
		if(length >= 5 && length <= 15) {
			char userName[LENGTH_CHAR];	
			
			generateUserName(length, userName);		
						
			sprintf(response,"[SERVER-INFO]: El nombre de usuario [%s] se genero correctamente.\n", userName);			
		}
		
		else {			
			strcpy(response, "[SERVER-ERROR]: El numero tiene que tener un minimo de 5 y un maximo de 15 de longitud.\n");
		}
	}
		
	else {
		deleteLineBreak(buffer);	
		strcpy(response, "[SERVER-ERROR]: Solo se permiten numeros.\n");
	}
}

void processMessageGeneratorPassword(char *buffer, char *response) {
	if(isNumber(buffer)) {
	
	int length = atoi(buffer);
	
		if(length >= 8 && length <= 50) {
			char password[LENGTH_CHAR];			
		
			generatePassword(length, password);
						
			sprintf(response,"[SERVER-INFO]: La clave de usuario [%s] se genero correctamente.", password);			
		}
		
		else {			
			strcpy(response, "[SERVER-ERROR]: La clave tiene que tener un minimo de 8 y un maximo de 50 de longitud.");
		}
	}
		
	else {
		deleteLineBreak(buffer);	
		strcpy(response, "[SERVER-ERROR]: Solo se permiten numeros.");
	}
}

void clearConsole() {
	system("cls");
}

void mainProcess(int option, char *response) {
	
	switch(option) {
		case 1:	
			strcpy(response, "[SERVER] Ingrese la longitud de su nombre de usuario:\n");			
			break;
		case 2:	
			strcpy(response, "[SERVER] Ingrese la longitud de su clave de usuario:\n");			
			break;
		case 3:
			strcpy(response, "[SERVER] Usted ha salido del programa correctamente.\n");			
			break;
		default:
			strcpy(response, "[SERVER] Opcion no encontrada.\n");			
			break;
	}	
}

void mainGenerator(char *buffer, char *response, int option) {
	
	switch(option) {
		case 1:
			option = (int) buffer[0] - VALUE_ASCII;
			processMessageGeneratorUsername(buffer, response);						
			break;
		case 2:
			option = (int) buffer[0] - VALUE_ASCII;
			processMessageGeneratorPassword(buffer, response);						
			break;
		default:
		strcpy(response, "[SERVER] Opcion no encontrada.\n");			
		break;
	}
}

int main() {
	
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
	    
    int socketSize;
    int optionSwitch;	
    
    char buffer[LENGTH_CHAR];
    char response[LENGTH_CHAR];    
    
    configServerSocket(&wsa, &server_socket, &server);

    listen(server_socket, 1);
	
	printf("[SERVIDOR]: Esperando una conexion... \n");
    
    socketSize = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr*)&client, &socketSize);
    
    printf("[SERVIDOR]: Conexion aceptada.\n");  
    
    ///////////////////////////////////////////////////////
    
  	memset(response, 0, sizeof(response));
  	
	recv(client_socket, buffer, LENGTH_CHAR, 0);
	
	optionSwitch = (int) buffer[0] - VALUE_ASCII;
	
	mainProcess(optionSwitch, response);
	
	 printf("[SERVIDOR]: Peticion enviada al cliente.\n");
	 
	 printf("[SERVIDOR]: Se le solicito al cliente: [%s]", response);
	 		
	send(client_socket, response, strlen(response), 0);
	
    ///////////////////////////////////////////////////////	
    
	memset(response, 0, sizeof(response));
	
	recv(client_socket, buffer, LENGTH_CHAR, 0);
	
	printf("[SERVIDOR]: Recibido la peticion del usuario: [%s]\n", buffer);

	mainGenerator(buffer, response, optionSwitch);
	
	printf("[SERVIDOR]: Respuesta enviada: %s\n", response);
	
	send(client_socket, response, strlen(response), 0);
	
    ///////////////////////////////////////////////////////
	 
    closesocket(client_socket);
    closesocket(server_socket);
    
    printf("[SERVIDOR]: Programa finalizado correctamente\n", buffer);

    WSACleanup();

    return 0;
}
