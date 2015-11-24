
const char * usage =
"                                                               \n"
"IRCServer:                                                   \n"
"                                                               \n"
"Simple server program used to communicate multiple users       \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   IRCServer <port>                                          \n"
"                                                               \n"
"Where 1024 < port < 65536.                                     \n"
"                                                               \n"
"In another window type:                                        \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where talk-server      \n"
"is running. <port> is the port number you used when you run    \n"
"daytime-server.                                                \n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "IRCServer.h"
#include "LinkedList.h"
#include "HashTableVoidS.h"



HashTableVoidS * roomsmsg;//KEY: room name, VALUE: LinkedList of Message of that room
HashTableVoidS * users;// KEY: user name, VALUE: password
HashTableVoidS * roomsusers; //KEY: room name, VALUE: LinkedList of Users
//FILE * ps;
const int MAX_MSG_SIZE = 1024;
int QueueLength = 5;

int
IRCServer::open_server_socket(int port) {

	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress;
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);

	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1;
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR,
			     (char *) &optval, sizeof( int ) );

	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
			  (struct sockaddr *)&serverIPAddress,
			  sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}

	// Put socket in listening mode and set the
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	return masterSocket;
}

void
IRCServer::runServer(int port)
{
	int masterSocket = open_server_socket(port);

	initialize();

	while ( 1 ) {

		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
					  (struct sockaddr *)&clientIPAddress,
					  (socklen_t*)&alen);

		if ( slaveSocket < 0 ) {
			perror( "accept" );
			exit( -1 );
		}

		// Process request.
		processRequest( slaveSocket );
	}
}

int
main( int argc, char ** argv )
{
	// Print usage if not enough arguments
	if ( argc < 2 ) {
		fprintf( stderr, "%s", usage );
		exit( -1 );
	}

	// Get the port from the arguments
	int port = atoi( argv[1] );

	IRCServer ircServer;

	// It will never return
	ircServer.runServer(port);

}

//
// Commands:
//   Commands are started y the client.
//
//   Request: ADD-USER <USER> <PASSWD>\r\n
//   Answer: OK\r\n or DENIED\r\n
//
//   REQUEST: GET-ALL-USERS <USER> <PASSWD>\r\n
//   Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
//   REQUEST: CREATE-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LIST-ROOMS <USER> <PASSWD>\r\n
//   Answer: room1\r\n
//           room2\r\n
//           ...
//           \r\n
//
//   Request: ENTER-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LEAVE-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE> <ROOM>\n
//   Answer: OK\n or DENIED\n
//
//   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-NUM> <ROOM>\r\n
//   Answer: MSGNUM1 USER1 MESSAGE1\r\n
//           MSGNUM2 USER2 MESSAGE2\r\n
//           MSGNUM3 USER2 MESSAGE2\r\n
//           ...\r\n
//           \r\n
//
//    REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD> <ROOM>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//

void
IRCServer::processRequest( int fd )
{
	// Buffer used to store the comand received from the client
	const int MaxCommandLine = 1024;
	char commandLine[ MaxCommandLine + 1 ];
	int commandLineLength = 0;
	int n;
	// Currently character read
	unsigned char prevChar = 0;
	unsigned char newChar = 0;

	//
	// The client should send COMMAND-LINE\n
	// Read the name of the client character by character until a
	// \n is found.
	//

	// Read character by character until a \n is found or the command string is full.
	while ( commandLineLength < MaxCommandLine &&
		read( fd, &newChar, 1) > 0 ) {

		if (newChar == '\n' && prevChar == '\r') {
			break;
		}

		commandLine[ commandLineLength ] = newChar;
		commandLineLength++;

		prevChar = newChar;
	}

	// Add null character at the end of the string
	// Eliminate last \r
	commandLineLength--;
        commandLine[ commandLineLength ] = 0;

	printf("RECEIVED: %s\n", commandLine);

	//printf("The commandLine has the following format:\n");
	//printf("COMMAND <user> <password> <arguments>. See below.\n");
	//printf("You need to separate the commandLine into those components\n");
	//printf("For now, command, user, and password are hardwired.\n");
	char * line[6];
	int i = 0;
	//line[i] = strdup(commandLine);
	char * originalCoomand = strdup(commandLine);
	line[i] = strtok(commandLine," ");
	while (line[i] != NULL && i<4){
		i++;
		line[i] = strtok(NULL," ");
	}
	if(i == 4 && (originalCoomand+strlen(line[0])+strlen(line[1])+strlen(line[2])+strlen(line[3])+4)!=NULL){
		line[4] = originalCoomand+strlen(line[0])+strlen(line[1])+strlen(line[2])+strlen(line[3])+4;
		i++;
	}
	for(;i<6;i++){
		line[i] = strdup("");
	}

	char * command = strdup(line[0]);
	char * user = strdup(line[1]);
	char * password = strdup(line[2]);

	char * args = strdup(line[3]);
	char * additional;
	if( line[4] != NULL){
		additional = strdup(line[4]);
	}
	else{
		additional = strdup("");
	}
	
	
	printf("COMMAND:%s\n", command);
	if (!strcmp(command, "ADD-USER")) {
		addUser(fd, user, password);
		//save_password_file(PASSWORD);
	}
	else if (!strcmp(command, "ENTER-ROOM")) {
		enterRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LEAVE-ROOM")) {
		leaveRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "SEND-MESSAGE")) {
		sendMessage(fd, user, password, args, additional);
		printf("MESSAGE:%s\n", additional); 
	}
	else if (!strcmp(command, "GET-MESSAGES")) {
		getMessages(fd, user, password, args,additional);
	}
	else if (!strcmp(command, "CREATE-ROOM")) {
		createRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LIST-ROOMS")) {
		listRoom(fd, user, password);
	}
	else if (!strcmp(command, "GET-USERS-IN-ROOM")) {
		getUsersInRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-ALL-USERS")) {
		getAllUsers(fd, user, password);
	}
	else {
		char * msg =  strdup("UNKNOWN COMMAND\r\n");
		write(fd, msg, strlen(msg));
		//read_password_file(PASSWORD);
	}

	// Send OK answer
	// msg =  strdup("OK\n";
	//write(fd, msg, strlen(msg));

	close(fd);
}

void
IRCServer::initialize()
{

	//ps = fopen(PASSWORD,"rw+");

	roomsmsg = new HashTableVoidS();
	users = new HashTableVoidS();
	roomsusers = new HashTableVoidS();
	
	read_password_file(PASSWORD);
	//usernames = (LinkedList*) malloc(sizeof(LinkedList));

	//llist_init(usernames);


	// Open password file

	// Initialize users in room

	// Initalize message list

}

bool
IRCServer::checkPassword(int fd,char * user, char * password) {
	// Here check the password
	//char * pa = strdup(password);
	if(users->check(user,password))
		return true;
	else{
		write(fd ,"ERROR (Wrong password)\r\n", strlen("ERROR (Wrong password)\r\n"));
		return false;
	}

	//return true;
}

void
IRCServer::addUser(int fd, char * user, char * password)
{
	// Here add a new user. For now always return OK.
	//int h = users->hash(user);
	char * msg;
	if(users->exists(user)){
		msg =  strdup("DENIED\r\n");
	}
	else{
		//llist_add(usernames, h);
		users->insertItem(user,password);
		msg =  strdup("OK\r\n");
	}



	write(fd, msg, strlen(msg));

	return;
}

void
IRCServer::createRoom(int fd, char * user, char * password,char * args)
{
		char * msg;
	if(!checkPassword(fd,user,password)){
		 msg =  strdup("DENIED\r\n");
		write(fd, msg, strlen(msg));
		return;
	}

	if(roomsusers->exists(args)){
		 msg =  strdup("DENIED\r\n");
	}
	else{
		//llist_add(usernames, h);
		LinkedList * u = (LinkedList*) malloc(sizeof(LinkedList));
		LinkedList * m = (LinkedList*) malloc(sizeof(LinkedList));
		llist_init(m);
		llist_init(u);



		roomsusers->insertItem(args,u);
		roomsmsg->insertItem(args,m);
		 msg =  strdup("OK\r\n");
	}



	write(fd, msg, strlen(msg));

	return;
}

void
IRCServer::listRoom(int fd, char * user, char * password)
{
	char * msg;
	LinkedList * list = (LinkedList*) malloc(sizeof(LinkedList));
	llist_init(list);
	if(!checkPassword(fd,user,password)){
		msg =  strdup("DENIED\r\n");
		write(fd, msg, strlen(msg));
		return;
	}
	HashTableVoidIterator * it = new HashTableVoidIterator(roomsusers);
	//char msg[1000];
	void * data;
	char * name;
	char * m;
	while(it->next(name,data)){
		//sprintf(name)
		//strcat(msg,name);
		//write(fd, name, strlen(name));
		//write(fd,"\r\n",strlen("\r\n"));
		//strcat(msg,"\r\n");
		llist_add(list,name);

	}
	llist_sort(list,1);
	for(int n = 1;n<=llist_number_elements(list);n++){
		llist_get_ith(list,n,&m);
		char mg[strlen(m)+2];
		sprintf(mg,"%s\r\n",m);
		write(fd, mg, strlen(mg));
	}
	free(list);

	write(fd,"\r\n",strlen("\r\n"));
	return;


}

void
IRCServer::enterRoom(int fd, char * user, char * password,char * args)
{
		char * msg;
		void * link;
	if(!checkPassword(fd,user,password)){
		// msg =  strdup("DENIED\r\n");
		//write(fd, msg, strlen(msg));
		return;
	}
	LinkedList * users;
	//LinkedList * msg;
	if(roomsusers->exists(args)){
		roomsusers->find(args,&link);
		users = (LinkedList *) link;
		//roomsmsg->find(args,msg);
		if(!llist_exists(users,user)){
			llist_add(users,strdup(user));
		}
		msg =  strdup("OK\r\n");



	}else{
		 msg =  strdup("ERROR (No room)\r\n");
	}

	write(fd, msg, strlen(msg));


}

void
IRCServer::leaveRoom(int fd, char * user, char * password,char * args)
{
		char * msg;
		void * link;
	if(!checkPassword(fd,user,password)){
		// msg =  strdup("DENIED\r\n");
		//write(fd, msg, strlen(msg));
		return;
	}
	LinkedList * users;
	//LinkedList * msg;
	if(roomsusers->exists(args)){
		roomsusers->find(args,&link);
		users = (LinkedList *) link;
		//roomsmsg->find(args,msg);
		if(!llist_remove(users,user)){
			msg =  strdup("ERROR (No user in room)\r\n");
		}
		else{
			msg =  strdup("OK\r\n");
		}
	}else{
		 msg =  strdup("DENIED\r\n");
	}
	write(fd, msg, strlen(msg));
}

void
IRCServer::sendMessage(int fd, char * user, char * password,char * room,char * args)
{
		char * msg;
		void * link;
	if(!checkPassword(fd,user,password)){
		// msg =  strdup("DENIED\r\n");
		//write(fd, msg, strlen(msg));
		return;
	}
	LinkedList * users;
	LinkedList * msgs;
	if(roomsusers->exists(room)){
		roomsusers->find(room,&link);
		users = (LinkedList *) link;
		if(!llist_exists(users,user)){
			//printf();
			msg =  strdup("ERROR (user not in room)\r\n");
			write(fd, msg, strlen(msg));
			return;
		}
		roomsmsg->find(room,&link);
		msgs = (LinkedList *) link;
		//char m[strlen(args)+strlen(user)+3];
		char * m = (char *) malloc(sizeof(char) * (strlen(args)+strlen(user)+6));
		sprintf(m,"%d %s %s\r\n",llist_number_elements(msgs),user,args);
		llist_add(msgs,strdup(m));
		//write(fd, ", strlen(msg));
		msg =  strdup("OK\r\n");
		//msg = strdup(m);

	}
	else{
		 msg =  strdup("DENIED\r\n");
	}
	write(fd, msg, strlen(msg));
}

void
IRCServer::getMessages(int fd,char * user, char * password, char * num,char * args)
{
		char * msg;
		void * link;
	if(!checkPassword(fd,user,password)){
		//msg =  strdup("DENIED\r\n");
		//write(fd, msg, strlen(msg));
		return;
	}
	LinkedList * users;
	LinkedList * msgs;
	if(roomsusers->exists(args)){
		roomsusers->find(args,&link);
		users = (LinkedList*) link;
		if(!llist_exists(users,user)){
			//printf("\n");
			msg =  strdup("ERROR (User not in room)\r\n");
			write(fd, msg, strlen(msg));
			return;
		}
		roomsmsg->find(args,&link);
		msgs = (LinkedList*) link;
		//char m[strlen(args)+strlen(user)+3];
		//sprintf(m,"%s:%s\r\n",user,args);
		char * m;
		//printf("%d\n", llist_number_elements(msgs));
		//int total = llist_number_elements(msgs);
		int n = llist_number_elements(msgs) - atoi(num);
		if(n<=0){
			msg = strdup("NO-NEW-MESSAGES\r\n");
		}
		else {
			for(;n>0;n--){
				llist_get_ith(msgs,n,&m);
				write(fd, m, strlen(m));
			}
			msg =  strdup("\r\n");
		}
	}else{
		//sprintf(msg,"ERROR (No room): %s\r\n", args);
		msg =  strdup("ERROR (No room)\r\n");
	}
	write(fd, msg, strlen(msg));
}

void
IRCServer::getUsersInRoom(int fd, char * user, char * password,char * args)
{
		char * msg;
		void * link;
		//LinkedList * list = (LinkedList*) malloc(sizeof(LinkedList));
		//llist_init(list);
	if(!checkPassword(fd,user,password)){
		// msg =  strdup("DENIED\r\n");
		//write(fd, msg, strlen(msg));
		return;
	}
	int n = 1;
	LinkedList * users;
	LinkedList * msgs;
	if(roomsusers->exists(args)){
		roomsusers->find(args,&link);
		users = (LinkedList*) link;
		// if(!llist_exists(users,user)){
			//printf("\n");
			// msg =  strdup("ERROR (User not in room)\r\n");
			// write(fd, msg, strlen(msg));
			// return;
		// }
		roomsmsg->find(args,&link);
		msgs = (LinkedList*) link;
		//char m[strlen(args)+strlen(user)+3];
		//sprintf(m,"%s:%s\r\n",user,args);
		char * m;
		if(llist_number_elements(users)>1){
			llist_sort(users,1);
		}
		for(;n<=llist_number_elements(users);n++){
			llist_get_ith(users,n,&m);
			char mg[strlen(m)+2];
			sprintf(mg,"%s\r\n",m);
			
			write(fd, mg, strlen(mg));
		}
		 msg =  strdup("\r\n");

	}else{
		 msg =  strdup("DENIED\r\n");
	}
	write(fd, msg, strlen(msg));
}

void
IRCServer::getAllUsers(int fd, char * user, char * password)
{
		char * msg;
		void * link;
		LinkedList * list = (LinkedList*) malloc(sizeof(LinkedList));
		llist_init(list);
	if(!checkPassword(fd,user,password)){
		// msg =  strdup("DENIED\r\n");
		//write(fd, msg, strlen(msg));
		return;
	}
	//printf("RECEIVED: step 1\n" );
	//HashTableVoidIterator * it = new HashTableVoidIterator(users);
	HashTableVoidIterator it(users);

	//LinkedList * data;
	char * name;
	//printf("RECEIVED: step 2\n" );
	while(it.next(name,link)){
		//printf("RECEIVED: step 3\n" );
		//data = (LinkedList*) link;
		//sprintf(name)
		//strcat(msg,name);
		//char name;
		//int num = llist_number_elements(data);
		//for(int i = 1; i<= num; i++){
		//	printf("RECEIVED: step 4\n" );
		//	llist_get_ith(data,i,name);
			llist_add(list,name);
			//write(fd, (char*) link, strlen((char*) link));
			//write(fd,"\r\n",strlen("\r\n"));

	}
	llist_sort(list,1);
	char * m;
	for(int n = 1;n<=llist_number_elements(list);n++){
		llist_get_ith(list,n,&m);
		char mg[strlen(m)+2];
		sprintf(mg,"%s\r\n",m);
			
		write(fd, mg, strlen(mg));
	}
	//write(fd, name, strlen(name));
	//write(fd,"\r\n",strlen("\r\n"));
	free(list);
	write(fd,"\r\n",strlen("\r\n"));
	return;


}

int 
IRCServer::save_password_file(const char * file_name){
	FILE * file = fopen(file_name,"wb");
	HashTableVoidIterator it(users);
	if(file == NULL)
		return 0;
	void * password;
	char * name;
	
	while(it.next(name,password)){
		fprintf(file,"%s\t%s\n", name,(char *)password);
	}
	fclose(file);
	return 1;
}

int 
IRCServer::read_password_file(const char * file_name){
	FILE * file = fopen(file_name,"r");
	//HashTableVoidIterator it(users);
	if(file == NULL)
		return 0;
	char password[100];
	char name[100];
	char * pas;
	printf("USER FILE FOUND\n");
	while( (fscanf(file,"%s%s", name,password)) != EOF ){
		//fprintf(file,"%s\t%s\n", name,(char *)password);
		printf("%s\t%s", name,password);
		if(users->exists(name)){
			//msg =  strdup("DENIED\r\n");
			printf("\tSKIPPED\n");
		}
		else{
			//llist_add(usernames, h);
			pas = (char*)malloc(strlen(password)*sizeof(char));
			sprintf(pas,"%s",password);
			users->insertItem(name,pas);
			//msg =  strdup("OK\r\n");
			printf("\tADDED\n");
		}
		
	}
	fclose(file);
	return 1;
}

