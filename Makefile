CC = gcc
CFLAGS = -lsqlite3 -Wall

all: main

main: main.c database.o users.o scores.o
	$(CC) main.c database.o users.o scores.o -o main $(CFLAGS)

database.o: database.c database.h
	$(CC) -c database.c -o database.o $(CFLAGS)

users.o: users.c users.h
	$(CC) -c users.c -o users.o $(CFLAGS)

scores.o: scores.c scores.h
	$(CC) -c scores.c -o scores.o $(CFLAGS)

clean:
	rm -f *.o main