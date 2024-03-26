CC = gcc
LFLAGS = -lm

SOURCES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SOURCES))

.PHONY: clean

all : coolness 

coolness : coolness.o
	$(CC) $(LFLAGS) -o coolness $(OBJECTS)

%.o : %.c
	$(CC) -c $<

test: coolness
	./testing.sh

clean:
	rm $(OBJECTS) coolness *.o
