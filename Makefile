all: 7colors

7colors: 7colors.o main.o
	gcc 7colors.o main.o -o 7colors

7colors.o: 7colors.c
	gcc -Wall -Werror -Wextra 7colors.c -c -g

main.o: main.c
	gcc -Wall -Werror -Wextra main.c -c -g