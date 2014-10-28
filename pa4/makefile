CC = gcc
CCFLAGS = -g

all: index

index: index.c
	$(CC) $(CCFLAGS) -o search search.c index.c tokenizer.c sorted-list.c

clean:
	-rm -f tokenizer.o
	-rm -f tokenizer
	-rm -f index.o
	-rm -f index
	-rm -f search
	-rm -f search.o
