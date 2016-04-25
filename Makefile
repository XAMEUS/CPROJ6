CC = gcc
CFLAGS = -Wall `sdl2-config --cflags` `xml2-config --cflags` `pkg-config --cflags glib-2.0` `libpng-config --cflags` -lm -lGLU
LDFLAGS= `sdl2-config --libs` `xml2-config --libs` `pkg-config --libs glib-2.0` `libpng-config  --libs` -lm -lGLU
EXEC = main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

%.o: %.c $(HEADERS)
	$(CC) -c $< $(CFLAGS)

main: display.o listref.o parse.o draw.o render.o ui.o main.o tessellation.o load.o
	$(CC) $^ -o osm -lGLU -lGL $(LDFLAGS)

drawing: display.o draw.o drawing.o tessellation.o
	$(CC) -o drawing $^ -lGLU -lGL $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

indent:
	indent -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -npsl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1 *.c -l125

mrproper: clean
	rm -f $(EXEC)
