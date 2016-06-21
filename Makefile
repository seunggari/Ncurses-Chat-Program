All : server client

server : server.o serversocket.o mydb.o
	gcc -o s server.o serversocket.o mydb.o -lncurses -lpthread -lmysqlclient

server.o : server.c serversocket.h
	gcc -c server.c 

serversocket : serversocket.c serversocket.h
	gcc -c serversocket.c 

client : client.o clientsocket.o
	gcc -o c client.o clientsocket.o -lncurses -lpthread

client.o : client.c clientsocket.h
	gcc -c client.c 

clientsocket : clientsocket.c clientsocket.h
	gcc -c clientsocket.c

mydb.o : mydb.c mydb.h
	gcc -c mydb.c

clean : 
	rm -rf s c *.o
