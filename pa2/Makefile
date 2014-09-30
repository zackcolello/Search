CC = gcc
CCFLAGS = -Wall -g 

all:	main sorted-list
	

main: main.o
	$(CC) $(CCFLAGS) -o main main.c
		

sorted-list: sorted-list.o
	$(CC) $(CCFLAGS) -o sorted-list sorted-list.c

clean:
	-rm -f sorted-list.o
	-rm -f sorted-list
	-rm -f main.o
	-rm -f main
