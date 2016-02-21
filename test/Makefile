CC = gcc
CFLAGS = -Wall `sdl2-config --cflags` `xml2-config --cflags` -lm
LDFLAGS= `sdl2-config --libs` `xml2-config --libs` -lm
EXEC = test_sdl0 test_sdl1 test_sdl2 test_sdl4 test_sdl5
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

test_sdl0: test_sdl0.o
	$(CC) -o test_sdl0 $^ $(LDFLAGS)

test_sdl1: test_sdl1.o
	$(CC) -o test_sdl1 $^ $(LDFLAGS)

test_sdl2: test_sdl2.o
	$(CC) -o test_sdl2 $^ $(LDFLAGS)

test_sdl4: test_sdl4.o
	$(CC) -o test_sdl4 $^ -lGLU -lGL $(LDFLAGS)

test_sdl5: test_sdl5.o
	$(CC) -o test_sdl5 $^ -lGLU -lGL $(LDFLAGS)

test_sdl6: test_sdl6.o parse.o
	$(CC) -o test_sdl6 $^ -lGLU -lGL $(LDFLAGS)


parse: parse.o
	$(CC) -o parse $^ $(LDFLAGS)

#$(EXEC) : $(OBJECTS)
#	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c $< '-lm' $(CFLAGS)

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
