OBJECTS=7colors.o main.o game.o ai.o list.o
EXECUTABLE=7colors

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	gcc $^ -o $@ -lm

%.o: %.c
	gcc -Wall -Werror -Wextra $(@:.o=.c) -c -g

clean:
	rm -f *.o *.dSYM
	rm -f $(EXECUTABLE)
