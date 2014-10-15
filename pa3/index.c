//here we will have our actual indexing/placing into our list.
//We can either have our main here or make a seperate main.c file.

#include <stdio.h>
#include <stdlib.h>
#include "index.h"


int main(int argc, char **argv){

	if(argc != 3){
		printf("Error: invalid number of arguments\n");
		return -1;

	}

	TokenizerT* tokenizer = TKCreate(argv[1], argv[2]);

	return 0;
}
