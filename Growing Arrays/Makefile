CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
T = growing_arrays
O = growing_arrays.o

all: $(T)

$(T): $(O)
	$(CC) $(CFLAGS) -o $(T) $(O)

growing_arrays.o: growing_arrays.c growing_arrays.h
	$(CC) $(CFLAGS) -c growing_arrays.c

clean:
	rm -f $(O) $(T)