CC = gcc
CCFLAGS = -g

all: index search

index: index.c
	$(CC) $(CCFLAGS) -o index index.c tokenizer.c sorted-list.c

search: search.c
	$(CC) $(CCFLAGS) -o search search.c parsefile.c bst.c

clean:
	-rm -f *.o
	-rm -f index
	-rm -f search
