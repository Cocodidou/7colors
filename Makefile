all: 7colors

7colors: 7colors.o main.o game.o
	gcc 7colors.o main.o game.o -o 7colors

7colors.o: 7colors.c
	gcc -Wall -Werror -Wextra 7colors.c -c -g

main.o: main.c
	gcc -Wall -Werror -Wextra main.c -c -g

game.o: game.c
	gcc -Wall -Werror -Wextra game.c -c -g
