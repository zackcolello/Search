//search.c -- our main function is here

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){

	if (argc != 2){
		fprintf(stderr, "Error: invalid number of arguments.\n");
		return -1;
	}

	//TODO: check if inputted inverse index file is valid
	//if file is valid, use index to make list from file
	
	char* input= malloc(1000); //need to make sure input does not go out of bounds

	//keep looping until input is 'q'

	while(fgets(input, 1000, stdin)){ //need to fix input != 'q'

		//put terminating bit at end of word, so we can quit with just 'q'
		input[strlen(input) -1] = '\0';
		
		//can't get it to break out, this doesn't work. 
		if (strcmp(input, "q") == 0){
			printf("Breaking\n");
			break;
		}

		printf("input is: %s\n", input);

	}

	printf("Session ended.\n");

	return 0;
}
