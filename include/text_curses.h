#ifndef __TEXT_CURSES_H_
#define __TEXT_CURSES_H_

#include <ncurses.h>
#include <string.h>

#define MAXERRS 7

#define WIN_OR_LOOSE_Y 12
#define WIN_OR_LOOSE_X 0
#define GUESS_Y 11
#define GUESS_X 0
#define WORD_Y 10
#define WORD_X 1
#define WORD_SHOP_Y 4
#define WORD_SHOP_X (COLS -1 -26)
#define CURRENT_AVG_Y 5
#define CURRENT_AVG_X (COLS -1 -26)
#define GUESSED_Y 2
#define GUESSED_X (COLS -1 -26)


typedef struct{
	short y,x;
	char ch;
}ERR_POS;

bool    Guessed[26];

char    Word[BUFSIZ], Known[BUFSIZ];

const char *const Noose_pict[] = {
	"     ______",
	"     |    |",
	"     |",
	"     |",
	"     |",
	"     |",
	"   __|_____",
	"   |      |___",
	"   |_________|",
	NULL
};

const ERR_POS Err_pos[MAXERRS] = {
	{2, 10, 'O'},
	{3, 10, '|'},
	{4, 10, '|'},
	{5, 9, '/'},
	{3, 9, '/'},
    {3, 11, '\\'},
    {5, 11, '\\'}
};

#endif
