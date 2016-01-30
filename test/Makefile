CC = gcc
CFLAGS = -Wall `sdl2-config --cflags`
LDFLAGS= `sdl2-config --libs`
EXEC = test_sdl0 test_sdl1
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

test_sdl0: test_sdl0.o
	$(CC) -o test_sdl0 $^ $(LDFLAGS)

test_sdl1: test_sdl1.o
	$(CC) -o test_sdl1 $^ $(LDFLAGS)

#$(EXEC) : $(OBJECTS)
#	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c $< '-lm' $(CFLAGS)

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
