#declare the variable
CC=gcc

CFLAGS=-c -Wall

all: driver

driver: driver.o read_write.o utilities.o commands.o
	$(CC) driver.o read_write.o utilities.o commands.o -o driver

driver.o: driver.c
	$(CC) $(CFLAGS) driver.c

read_write.o: read_write.c
	$(CC) $(CFLAGS) read_write.c

utilities.o: utilities.c
	$(CC) $(CFLAGS) utilities.c	

commands.o: commands.c
	$(CC) $(CFLAGS) commands.c

clean:
	rm -rf *o server
	
