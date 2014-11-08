//parsefile.c -- parses inverted index file

#include <stdio.h>
#include <stdlib.h>
#include "sorted-list.h"
#include "parsefile.h"



struct List buildLL(FILE *filep){
	
	int c, i;
	char* buffer = (char*)malloc(1000);
	char* testbuff = "<list> ";
	char testbuff2[8];
	char* trimmedbuffer;


	while(fgets(buffer, 1000, filep)){

		strncpy(testbuff2, buffer, 7);

		if(strcmp(testbuff2, testbuff) == 0){
			printf("this dudes a token: %s \n", buffer);	
			
			trimmedbuffer = (char*)malloc(sizeof(buffer) - 6);

			trimmedbuffer = &buffer[7];
			printf("new buffer is now %s\n", trimmedbuffer);
		}
	}

	buffer[i+1] = '\0';


}

