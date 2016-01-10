OPTIMIZE = -O2

CC = gcc
CFLAGS = $(OPTIMIZE) -g

default: simpsh

simpsh: simpsh.c
	$(CC) $(CFLAGS) simpsh.c -o $@


clean:
	rm -f *.o simpsh