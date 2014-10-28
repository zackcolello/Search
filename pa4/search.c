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
	
	//keep looping until input is 'q'
	char* input[100]; //need to make sure input does not go out of bounds

	while(scanf("%s", &input) && input != 'q'){ //need to fix input != 'q'
		//just used for debugging
		//	printf("input is: %s\n", input);

	}

	printf("Session ended.\n");

	return 0;
}
