
#ifndef IRC_SERVER
#define IRC_SERVER





#define PASSWORD "pas.txt"


class IRCServer {
	// Add any variables you need


private:
	int open_server_socket(int port);

public:
	void initialize();
	bool checkPassword(int fd,char * user, char * password);
	void processRequest( int socket );
	void addUser(int fd, char * user, char * password);
	void enterRoom(int fd, char * user, char * password, char * args);
	void createRoom(int fd, char * user, char * password, char * args);
	void leaveRoom(int fd, char * user, char * password, char * args);
	void sendMessage(int fd, char * user, char * password, char * args, char * room);
	void getMessages(int fd, char * user, char * password, char * num,char * args);
	void listRoom(int fd, char * user, char * password);
	void getUsersInRoom(int fd, char * user, char * password, char * args);
	void getAllUsers(int fd, char * user, char * password);
	void runServer(int port);
	int save_password_file(const char * file_name);
	int read_password_file(const char * file_name);
};

#endif