CC = gcc
CCFLAGS = -g

index: index.o
	$(CC) $(CCFLAGS) -o index index.c

clean:
	-rm -f tokenizer.o
	-rm -f tokenizer
	-rm -f index.o
	-rm -f index
