#include "my_hangman.h"
#include "text_hangman_func_list.h"

int main(int argc, char *argv[]){
	
	char *path = "/home/s/C_Programing/hangman_project_sg2/etc/wordlist";
	int min_word_length=MINIMUM_WORD_LENGTH;
	
	arg_list_set_up(argc,argv,&path,&min_word_length);
	load_word_list(path);

	init_screen();
	play_hangman(min_word_length);

	endwin();

	return 0;
}
