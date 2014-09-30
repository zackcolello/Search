CC = gcc

all:	main sorted-list
	

main: main.o
	gcc -g -Wall -o main main.c


sorted-list: sorted-list.o
	gcc -g -Wall -o sorted-list sorted-list.c

clean:
	-rm -f sorted-list.o
	-rm -f sorted-list
	-rm -f main.o
	-rm -f main
