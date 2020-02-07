CC=gcc
IDIR = include/
OBJDIR = obj/
SRCDIR = src/
SRC = $(wildcard src/*.c)
CFLAGS = -Wall -I$(IDIR)

LDFLAGS = -lm -lglfw -lGL -lglut -lGLESv2 -lEGL -lX11
glprog: $(SRCDIR) $(SRC)
	${CC} $(CFLAGS) $(SRC) ${LDFLAGS} -o glprog
