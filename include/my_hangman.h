#ifndef __MY_HANGMAN_H_
#define __MY_HANGMAN_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_NUMBER_OF_WORDS 200
#define NUMBER_OF_CHANCE 7
#define MINIMUM_WORD_LENGTH 5
#define GUESSED_WORD_LENGTH 30
#define PATH_LENGTH 50

typedef struct{
	int length;
	char *ptr_text;
}_WORD;

typedef struct{
	int count;
	_WORD *ptr_word_array[MAXIMUM_NUMBER_OF_WORDS];
	int maximum_word_length;
}_WORD_LIST;

_WORD word;

_WORD_LIST *ptr_word_list;

#endif
