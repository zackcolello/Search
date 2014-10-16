CC = gcc
CCFLAGS = -g

all: index

index: index.c
	$(CC) $(CCFLAGS) -o index index.c tokenizer.c

clean:
	-rm -f tokenizer.o
	-rm -f tokenizer
	-rm -f index.o
	-rm -f index
