CC = gcc
LFLAGS = 

SOURCES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SOURCES))

.PHONY: clean

all : histogram 

histogram : histogram.o
	$(CC) $(LFLAGS) -o histogram $(OBJECTS)

%.o : %.c
	$(CC) -c $<

test: histogram
	./testing.sh

clean:
	rm $(OBJECTS) histogram *.o
