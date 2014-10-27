/*
 * tokenizer.c
 * Written by Zack Colello and Anna Genke
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

char *indexPointer; //to be used to track where tokens are in the second argument.

/*
 *  * TKCreate creates a new TokenizerT object for a given set of separator
 *   * characters (given as a string) and a token stream (given as a string).
 *    * 
 *     * TKCreate should copy the two arguments so that it is not dependent on
 *      * them staying immutable after returning.  (In the future, this may change
 *       * to increase efficiency.)
 *        *
 *         * If the function succeeds, it returns a non-NULL TokenizerT.
 *          * Else it returns NULL.
 *           *
 *            * You need to fill in this function as part of your implementation.
 *             */

TokenizerT *TKCreate(char *ts) {

	TokenizerT *temptok;

	int StringSize = strlen(ts); 
	
	temptok = malloc(sizeof(TokenizerT));
	temptok->input = (char*) malloc(StringSize +1);
  
	strcpy(temptok->input, ts);

		return temptok;
}

/*
 *  * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 *   * allocated memory that is part of the object being destroyed.
 *    *
 *     * You need to fill in this function as part of your implementation.
 *      */

void TKDestroy(TokenizerT *tk) {

	free(tk);
	tk = NULL;


}


/*
 *  * TKGetNextToken returns the next token from the token stream as a
 *   * character string.  Space for the returned token should be dynamically
 *    * allocated.  The caller is responsible for freeing the space once it is
 *     * no longer needed.
 *      *
 *       * If the function succeeds, it returns a C string (delimited by '\0')
 *        * containing the token.  Else it returns 0.
 *         *
 *          * You need to fill in this function as part of your implementation.
 *           */

char *TKGetNextToken(TokenizerT *tk) {

	int i, b, BBIndex;
	BBIndex = 0;

	char c;
	char* BigBuffer; //to be used for returning tokens

	BigBuffer = (char*) malloc(1000);
	
	for(i = 0; i<(strlen(indexPointer)+1); i++){

		c = (indexPointer[i]);
		b = isDelimiter(c, tk);	

		if(c == '\0'){
		
			BigBuffer[BBIndex] = '\0';
			indexPointer = '\0';			

			return BigBuffer;


		}

		if(b == 0){ //not delimiter, add to BigBuffer
			
			BigBuffer[BBIndex]=c;
			BBIndex++;

			
		}else{ //is delimiter, return now

			indexPointer = &tk->input[i+1];
			tk->input = indexPointer;
			BigBuffer[BBIndex] = '\0';
			
			return BigBuffer;
		}

	}


  return 0;
}


/* Function isDelimiter is used by main to check if a character in the second argument is a delimiter.
 * isDelimiter uses tokenizer's delimiters value to compare a character with those delimiter values.
 * It returns 1 if the character is in the delimiter string, and 0 otherwise.
 * */
int isDelimiter(char c, TokenizerT *tokenizer){


	if(!isalnum(c)){
		return 1;
	}	

	return 0;	//character c was not found to be a delimiter. Return 0 for false

}
