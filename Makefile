CC = gcc
CFLAGS = -Wall `sdl2-config --cflags` `xml2-config --cflags` -lm
LDFLAGS= `sdl2-config --libs` `xml2-config --libs` -lm
EXEC = main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

%.o: %.c $(HEADERS)
	$(CC) -c $< '-lm' $(CFLAGS)

main: display.o listref.o parse.o draw.o render.o ui.o main.o
	$(CC) $^ -lGLU -lGL $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
