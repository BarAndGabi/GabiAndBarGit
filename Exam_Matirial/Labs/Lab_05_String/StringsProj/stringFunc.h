#ifndef STRINGFUNC_H_
#define STRINGFUNC_H_

#define MAX_LENGTH  100

int 	countCapitalLetters(const char* str);
int		mostCapitalCountWord(const char* str,char* theWord);

void	fixString(char* str);
void	arrOfStrings(char* mat, int rows, int cols);
int  	countWords(char * str);

char*	myGets(char* buf, int size);


#endif /* STRINGFUNC_H_ */
