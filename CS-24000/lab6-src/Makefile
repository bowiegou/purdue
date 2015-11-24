
CXX = g++ -fPIC

all:  IRCServer HashTableVoidTest

HashTableVoidTest: HashTableVoidTest.cc
	g++ -g -o HashTableVoidTest HashTableVoid.cc HashTableVoidTest.cc
	
IRCServer: IRCServer.cc
	g++ -g -o IRCServer HashTableVoidS.cc LinkedList.c IRCServer.cc
	git add -A  >> .local.git.out
	git commit -a -m "Make IRCServer" >> .local.git.out

clean:
	rm -f *.out
	rm -f *.o HashTableVoidTest IRCServer


