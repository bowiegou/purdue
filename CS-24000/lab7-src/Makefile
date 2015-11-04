
goal: hello entry panned radio timer IRCClient IRCServer

IRCServer: IRCServer.cc
	g++ -g -o IRCServer HashTableVoidS.cc LinkedList.c IRCServer.cc
	
hello: hello.c
	gcc hello.c -o hello `pkg-config --cflags --libs gtk+-2.0`

IRCClient: IRCClient.cc
	g++ IRCClient.cc -g -o IRCClient `pkg-config --cflags --libs gtk+-2.0` talk-client.c LinkedList.c

panned: panned.c
	gcc panned.c -o panned `pkg-config --cflags --libs gtk+-2.0`


entry: entry.c
	gcc entry.c -o entry `pkg-config --cflags --libs gtk+-2.0`

radio: radio.c
	gcc radio.c -o radio `pkg-config --cflags --libs gtk+-2.0`

timer: timer.c
	gcc timer.c -o timer `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -f hello panned entry radio timer TestIRCServer IRCClient IRCServer

