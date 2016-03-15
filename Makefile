CC = gcc
CFLAGS = -Wall `sdl2-config --cflags` `xml2-config --cflags` `pkg-config --cflags glib-2.0` -lm
LDFLAGS= `sdl2-config --libs` `xml2-config --libs` `pkg-config --libs glib-2.0` -lm
EXEC = main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

%.o: %.c $(HEADERS)
	$(CC) -c $< $(CFLAGS)

main: display.o listref.o parse.o draw.o render.o ui.o main.o
	$(CC) $^ -lGLU -lGL $(LDFLAGS)

drawing: display.o draw.o drawing.o
	$(CC) -o drawing $^ -lGLU -lGL $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
