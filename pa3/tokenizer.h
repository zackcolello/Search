#include <stdio.h>
#include<stdlib.h>

struct TokenizerT_ {
	char* delimiters;
	char* input;
};
typedef struct TokenizerT_ TokenizerT;

int isDelimiter (char c, TokenizerT *tokenizer);
char *indexPointer;

TokenizerT *TKCreate(char *its); 
void TKDestroy(TokenizerT *tk);
char *Translate (char *untranslated);	
char *TranslateHexString (char *HexString);
char *TrimBuffer (char *buffer);
char *TKGetNextToken(TokenizerT *tk);
int isDelimiter(char c, TokenizerT *tokenizer);	
