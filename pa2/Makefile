CC = gcc
CCFLAGS = -Wall -g 

all:	main	 

main: main.o libsl.a
	$(CC) $(CCFLAGS) -o sl main.c libsl.a
	
libsl.a: sorted-list.o
	ar -rv libsl.a sorted-list.o	

sorted-list: sorted-list.o
	$(CC) $(CCFLAGS) -o sorted-list sorted-list.c

clean:
	-rm -f sorted-list.o
	-rm -f sorted-list
	-rm -f main.o
	-rm -f main
	-rm -f sl
	-rm -f *.a
