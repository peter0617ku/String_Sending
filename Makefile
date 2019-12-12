CC=gcc
CFALG=-c
OFLAG=-o

all:server.o client.o
	$(CC) $(OFLAG) server.exe server.o
	$(CC) $(OFLAG) client.exe client.o
server.o:
	$(CC) $(CFLAG) server.c
client.o:
	$(CC) $(CFLAG) client.c
clean:
	rm *.exe *.o
