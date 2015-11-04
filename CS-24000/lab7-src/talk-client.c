
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "talk-client.h"

char * host;
char * user;
char * password;
char * sport;
int port;

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LEN 300
#define MAX_RESPONSE (20 * 1024)

int lastMessage = 0;

int open_client_socket(char * host, int port) {
	// Initialize socket address structure
	struct  sockaddr_in socketAddress;
	
	// Clear sockaddr structure
	memset((char *)&socketAddress,0,sizeof(socketAddress));
	
	// Set family to Internet 
	socketAddress.sin_family = AF_INET;
	
	// Set port
	socketAddress.sin_port = htons((u_short)port);
	
	// Get host table entry for this host
	struct  hostent  *ptrh = gethostbyname(host);
	if ( ptrh == NULL ) {
		perror("gethostbyname");
		//exit(1);
		return -1;
	}
	
	// Copy the host ip address to socket address structure
	memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);
	
	// Get TCP transport protocol entry
	struct  protoent *ptrp = getprotobyname("tcp");
	if ( ptrp == NULL ) {
		perror("getprotobyname");
		//exit(1);
		return -1;
	}
	
	// Create a tcp socket
	int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if (sock < 0) {
		perror("socket");
		//exit(1);
		return -1;
	}
	
	// Connect the socket to the specified server
	if (connect(sock, (struct sockaddr *)&socketAddress,
		    sizeof(socketAddress)) < 0) {
		perror("connect");
		//exit(1);
		return -1;
	}
	
	return sock;
}

int sendCommand(char * host, int port, char * command, char * user,
		char * password, char * args, char * add, char * response) {
	int sock = open_client_socket( host, port);
	
	if(sock == -1){
		sprintf(response, "ERROR on open socket, host name: %s ,port: %d", host, port);
		return -1;
	}		
	// Send command
	write(sock, command, strlen(command));
	write(sock, " ", 1);
	write(sock, user, strlen(user));
	write(sock, " ", 1);
	write(sock, password, strlen(password));
	if(args != NULL){
		write(sock, " ", 1);
		write(sock, args, strlen(args));
		if(add != NULL) {
			write(sock, " ", 1);
			write(sock, add, strlen(add));
		}
	}
	write(sock, "\r\n",2);

	// Keep reading until connection is closed or MAX_REPONSE
	int n = 0;
	int len = 0;
	while ((n=read(sock, response+len, MAX_RESPONSE - len))>0) {
		len += n;
	}
	response[len]=0;

	//printf("response:%s\n", response);

	close(sock);
}

void printUsage()
{
	printf("Usage: talk-client host port user password\n");
	exit(1);
}

int check_password(char * host, int port, char * user, char * password){
	char response[ MAX_RESPONSE ];
	sendCommand(host, port, strdup("GET-ALL-USERS"), user, password, NULL,NULL, response);
	if(!strcmp(response,"ERROR (Wrong password)\r\n")){
		return 1;
	}
	return 0;
}

void add_user(char * host, int port, char * user, char * password, char **  r) {
	// Try first to add user in case it does not exist.
	char response[ MAX_RESPONSE ];
	sendCommand(host, port, strdup("ADD-USER"), user, password, NULL,NULL, response);
	
	if (!strcmp(response,"OK\r\n")) {
		printf("User %s added\n", user);
	} else {
		printf("ERROR on ADD-USER, User %s\n", user);
	}
	printf("Messages from Server: %s\n", response);
	
	*r = response;
}

void create_room(char * host, int port, char * user, char * password,char * room, char **  r) {
	char response[ MAX_RESPONSE ];
	sendCommand(host, port, strdup("CREATE-ROOM"), user, password, room, NULL, response);
	
	if (!strcmp(response,"OK\r\n")) {
		printf("CREATE-ROOM %s , user %s\n", room,user);
	} else {
		printf("ERROR on CREATE-ROOM, User %s\n", user);
	}
	printf("Messages from Server: %s\n", response);
	
	*r = response;
}

void enter_room(char * host, int port, char * user, char * password, char * room, char **  r) {
	char response[ MAX_RESPONSE ];
	sendCommand(host, port, strdup("ENTER-ROOM"), user, password, room, NULL, response);
	
	if (!strcmp(response,"OK\r\n")) {
		printf("Entered Room %s\n", room);
	} else {
		printf("ERROR on ENTER-ROOM, Room %s\n", room);
	}
	printf("Messages from Server: %s\n", response);
	
	*r = response;
}

void leave_room(char * host, int port,char * user, char * password, char * room, char **  r) {
	char response[ MAX_RESPONSE ];
	sendCommand(host, port, strdup("LEAVE-ROOM"), user, password, room, NULL, response);
	
	if (!strcmp(response,"OK\r\n")) {
		printf("LEAVE-ROOM Room %s\n", room);
	} else {
		printf("ERROR on LEAVE-ROOM, Room %s\n", room);
	}
	printf("Messages from Server: %s\n", response);
	
	*r = response;
}

int get_messages(char * host, int port,char * user, char * password, int msg_num,char * room, LinkedList **  r) {
	char response[ MAX_RESPONSE ];
	char * pch;
	char * tt;
	int i = 1;
	char num[20*1024];
	sprintf(num, "%d", msg_num);
	LinkedList * link = (LinkedList *) malloc (sizeof(LinkedList));
	llist_init(link);
	sendCommand(host, port, strdup("GET-MESSAGES"), user, password, num, room, response);
	

		printf("GET-MESSAGES, Room %s User %s\n", room, user);
	
	printf("Messages from Server: %s\n", response);
	
	if(!strcmp(response,"NO-NEW-MESSAGES\r\n")){
		return 2;
	}
	pch =strtok(response, "\r\n");
	while(pch != NULL){
		printf("Messages: %s\n", pch);
		llist_add(link, pch);
		pch = strtok(NULL, "\r\n");
	}
	
	
	
	*r = link;
	return 1;
}

void send_message(char * host, int port,char * user, char * password, char * room,char * msg, char **  r) {
	char response[ MAX_RESPONSE ];
	sendCommand(host, port, strdup("SEND-MESSAGE"), user, password, room, msg, response);
	
	if (!strcmp(response,"OK\r\n")) {
		printf("SEND-MESSAGE Succeed Room %s User %s\n", room, user);
	} else {
		printf("ERROR on SEND-MESSAGE, Room %s User %s\n", room, user);
	}
	printf("Messages from Server: %s\n", response);
	
	*r = response;
}

void print_rooms(char * host, int port,char * user, char * password, LinkedList **  r){
	char response[ MAX_RESPONSE ];
	char * pch;
	LinkedList * link = (LinkedList *) malloc (sizeof(LinkedList));
	llist_init(link);
	sendCommand(host, port, strdup("LIST-ROOMS"), user, password, NULL, NULL, response);
	
	printf("LIST-ROOMS User %s\n", user);
	printf("Messages from Server: %s\n", response);
	
	pch =strtok(response, "\r\n");
	while(pch != NULL){
		printf("Room: %s\n", pch);
		llist_add(link, pch);
		pch = strtok(NULL, "\r\n");
	}
	
	////llist_sort(link, 1);
	
	*r = link;
}

void print_users_in_room(char * host, int port,char * user, char * password, char * room, LinkedList **  r) {
	char response[ MAX_RESPONSE ];
	char * pch;
	LinkedList * link = (LinkedList *) malloc (sizeof(LinkedList));
	llist_init(link);
	sendCommand(host, port, strdup("GET-USERS-IN-ROOM"), user, password, room, NULL, response);
	
		printf("GET-USERS-IN-ROOM, Room %s User %s\n", room, user);
		
	printf("Messages from Server: %s\n", response);
	
	pch =strtok(response, "\r\n");
	while(pch != NULL){
		printf("User: %s\n", pch);
		llist_add(link, pch);
		pch = strtok(NULL, "\r\n");
	}
	
	////llist_sort(link, 1);
	*r = link;
}

void print_users(char * host, int port,char * user, char * password, LinkedList **  r) {
	char response[ MAX_RESPONSE ];
	char * pch;
	LinkedList * link = (LinkedList *) malloc (sizeof(LinkedList));
	llist_init(link);
	sendCommand(host, port, strdup("GET-ALL-USERS"), user, password, NULL, NULL, response);
	
		printf("GET-ALL-USERS, User %s\n", user);
		
	printf("Messages from Server: %s\n", response);
	
	pch =strtok(response, "\r\n");
	while(pch != NULL){
		printf("User: %s\n", pch);
		llist_add(link, pch);
		pch = strtok(NULL, "\r\n");
	}
	
	//llist_sort(link, 1);
	*r = link;
}

void printPrompt() {
	printf("talk> ");
	fflush(stdout);
}

void printHelp() {
	printf("Commands:\n");
	printf(" -who   - Gets users in room\n");
	printf(" -users - Prints all registered users\n");
	printf(" -help  - Prints this help\n");
	printf(" -quit  - Leaves the room\n");
	printf("Anything that does not start with \"-\" will be a message to the chat room\n");
}

void * getMessagesThread(void * arg) {
	// This code will be executed simultaneously with main()
	// Get messages to get last message number. Discard the initial Messages
	
	while (1) {
		// Get messages after last message number received.

		// Print messages

		// Sleep for ten seconds
		usleep(2*1000*1000);
	}
}

void startGetMessageThread()
{
	//pthread_create(NULL, NULL, getMessagesThread, NULL);
}


/* int main(int argc, char **argv) {

	char line[MAX_MESSAGE_LEN+1];
	
	if (argc < 5) {
		printUsage();
	}

	host = argv[1];
	sport = argv[2];
	user = argv[3];
	password = argv[4];

	printf("\nStarting talk-client %s %s %s %s\n", host, sport, user, password);

	// Convert port to number
	sscanf(sport, "%d", &port);

	add_user();

	// Enter room
	enter_room();

	// Start message thread
	startGetMessageThread();

	while (1) {
		printPrompt();

		char * s = fgets(line,MAX_MESSAGE_LEN, stdin);
		if (s==NULL) {
			leave_room();
			printf("talk-client exiting...\n");
			exit(1);
		}

		if (!isatty(0)) {
			// If it is not a terminal, echo command as well
			printf("%s\n", line);
		}

		if (line[0]=='-') {
			// This is a command process it
			if (!strcmp(line,"-help")) {
				printHelp();
			}
			else if (!strcmp(line,"-quit")) {
				printf("talk-client exiting...\n");
				exit(1);
			}
			// Put other commands here
		}
		else if (line[0]==0) {
			// Empty line. Print help
			printf("Type -help to print the available commands\n");
		}
		else {
			// Send message
		}
	}
	
	printf("TEST ENDS\n");
	return 0;
} */
