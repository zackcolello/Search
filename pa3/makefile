CC = gcc
CCFLAGS = -g

all: index tokenizer

index: index.o
	$(CC) $(CCFLAGS) -o index index.c

tokenizer: tokenizer.o
	$(CC) $(CCFLAGS) -o tokenizer tokenizer.c

clean:
	-rm -f tokenizer.o
	-rm -f tokenizer
	-rm -f index.o
	-rm -f index
