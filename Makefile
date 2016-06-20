All : server client

server : server.o serversocket.o
	gcc -o s server.o serversocket.o -lncurses -lpthread

ssrver.o : server.c serversocket.h
	gcc -c server.c 

serversocket : serversocket.c serversocket.h
	gcc -c serversocket.c 

client : client.o clientsocket.o
	gcc -o c client.o clientsocket.o -lncurses -lpthread

client.o : client.c clientsocket.h
	gcc -c client.c 

clean : 
	rm -rf s c *.o
