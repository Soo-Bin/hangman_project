#ifndef __TEXT_HANGMAN_FUNC_LIST_H_
#define __TEXT_HANGMAN_FUNC_LIST_H_

int test();
int arg_list_set_up(int f_argc, char *f_argv[], char **ptr_path, int *ptr_mwl);
void load_word_list(char *ptr_path);
void init_screen();
int play_hangman(int min_word_length);

#endif
