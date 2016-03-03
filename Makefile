OBJECTS=7colors.o main.o game.o ai.o list.o

all: 7colors

7colors: $(OBJECTS)
	gcc $^ -o 7colors -lm

%.o: %.c
	gcc -Wall -Werror -Wextra $(@:.o=.c) -c -g
