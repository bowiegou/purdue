
#include "LinkedList.h"
int open_client_socket(char * host, int port);
int sendCommand(char * host, int port, char * command, char * user,
		char * password, char * args, char * response);
void printUsage();
int check_password(char * host, int port, char * user, char * password);
void create_room(char * host, int port, char * user, char * password,char * room, char **  r);
void add_user(char * host, int port, char * user, char * password, char **  r);
void enter_room(char * host, int port,char * user, char * password, char * room, char **  r);
void leave_room(char * host, int port,char * user, char * password, char * room, char **  r);
int get_messages(char * host, int port,char * user, char * password, int msg_num, char * room, LinkedList **  r);
void send_message(char * host, int port,char * user, char * password, char * room,char * msg, char **  r);
void print_rooms(char * host, int port,char * user, char * password, LinkedList **  r);
void print_users_in_room(char * host, int port,char * user, char * password, char * room, LinkedList **  r);
void print_users(char * host, int port,char * user, char * password, LinkedList **  r);
void print_users();
void printPrompt();
void printHelp();
void * getMessagesThread(void * arg);
void startGetMessageThread();
