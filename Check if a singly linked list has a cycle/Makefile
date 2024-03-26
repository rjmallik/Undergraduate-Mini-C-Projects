# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

all: check_cycle

check_cycle: ll_cycle.o test_ll_cycle.o
	$(CC) $(CFLAGS) -o check_cycle ll_cycle.o test_ll_cycle.o

ll_cycle.o: ll_cycle.c ll_cycle.h
	$(CC) $(CFLAGS) -c ll_cycle.c

test_ll_cycle.o: test_ll_cycle.c ll_cycle.h
	$(CC) $(CFLAGS) -c test_ll_cycle.c

clean:
	rm -f check_cycle *.o
