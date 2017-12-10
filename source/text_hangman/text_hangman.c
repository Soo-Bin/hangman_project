#include "my_hangman.h"
#include "text_hangman.h"
#include "text_curses.h"

int test(){
	printf("\n");
	printf("text hangman function test called...!!!\n");
	printf("\n");
	
	return 0;
}

int arg_list_set_up(int f_argc, char *f_argv[], char **ptr_path, int *ptr_mwl){

	if(f_argc>1){
		if(strcmp(f_argv[1], "-h") ==0){
			printf("\nhangman command line arguments: \n");
			printf("\t-p path: path to a white space separated list of words \n");
			printf("\t-s size: minimum word length\n\n");
			return 0;
		}
		else{
			int arg_index=1;
			do{
				if(strcmp(f_argv[arg_index],"-p")==0){
					if(arg_index+1 <f_argc){
						arg_index++;
					}
				else{
					printf("\n-p option requires a wordlist path\n");
					return 1;
				}
				*ptr_path=f_argv[arg_index];
				printf("given path: %s\n",*ptr_path);
				}

				if(strcmp(f_argv[arg_index],"-s")==0){
					if(arg_index+1 <f_argc){
						arg_index++;
					}
				else{
					printf("\n-s option requires a wordlist path\n");
					return 1;
				}
				*ptr_mwl = strtol(f_argv[arg_index],NULL,0);
				printf("given minimum length: %d\n",*ptr_mwl);
				}
				arg_index++;
			}
			while(arg_index < f_argc);
		}
		return 0;
	}
}

void init_screen(){
	
	initscr();
	noecho();
	cbreak();
	clear();

	mvaddstr(GUESS_Y, GUESS_X, "Guess:");
	mvaddstr(GUESSED_Y, GUESSED_X, "Guessed:");
	mvaddstr(WORD_SHOP_Y, WORD_SHOP_X, "Word ##:");
	mvaddstr(CURRENT_AVG_Y, CURRENT_AVG_X, "Current Average:");
	mvaddstr(CURRENT_AVG_Y+1, CURRENT_AVG_X, "Overall Average:");
	mvaddstr(WORD_Y, WORD_X, "Word:");

	const char *const *sp;
	for(sp=Noose_pict; *sp!=NULL; sp++){
		move(sp-Noose_pict,0);
		addstr(*sp);
	}
	move(GUESS_Y, GUESS_X+sizeof"Guess: ");
	
	refresh();

}

void load_word_list(char *ptr_path){
	
	char temp[30];
	int index=0;

	ptr_word_list = malloc(sizeof(_WORD_LIST));
	ptr_word_list->maximum_word_length =1;
	
	FILE *ptr_word_file;
	ptr_word_file = fopen(ptr_path, "r");
	if(ptr_word_file == NULL){
		printf("\nNo such file or directory at %s\n\n",ptr_path);
		exit(0);
	}

	while(fscanf(ptr_word_file, "%s", temp) != EOF){
		int length = strlen(temp);

		if(ptr_word_list->maximum_word_length < length){
			ptr_word_list->maximum_word_length = length;
		}
		ptr_word_list->ptr_word_array[index] = malloc(sizeof(_WORD));
		ptr_word_list->ptr_word_array[index]->ptr_text = malloc(length*sizeof(char)+1);
		strcpy(ptr_word_list->ptr_word_array[index]->ptr_text, temp);
		ptr_word_list->ptr_word_array[index]->length = length;

		index++;

		if(index > MAXIMUM_NUMBER_OF_WORDS-1){

			printf("\nword storage space is full~~~\n\n");
			printf("index: %d~~~\n\n",index);
			break;
		}
	}
	ptr_word_list->count = index;

	fclose(ptr_word_file);
}

 int play_hangman(int min_word_length){
	
	int word_number=1,correct=0;
	float cur_avg=0,over_avg=0;
	srand(time(NULL));

	do{
		_WORD *ptr_random_word;
		do{
			ptr_random_word = ptr_word_list->ptr_word_array[rand()%ptr_word_list->count];
		}while(ptr_random_word->length < min_word_length);
		
		char guess,answer;
		int chances = NUMBER_OF_CHANCE;
		int Maxers=0;
		char guessed[GUESSED_WORD_LENGTH]="";
		char hidden_word[ptr_random_word->length+1];
		
		memset(hidden_word, '\0', ptr_random_word->length+1);
		memset(hidden_word, '_', ptr_random_word->length);

		move(WORD_Y, WORD_X+sizeof"Word: ");
		printw("%s",hidden_word);
		move(WORD_SHOP_Y, WORD_SHOP_X+sizeof"Word ##: ");
		printw("\t  %d",word_number);
		move(CURRENT_AVG_Y, CURRENT_AVG_X+sizeof"Current Average: ");
		printw("%.3f",cur_avg/word_number);
		move(CURRENT_AVG_Y+1, CURRENT_AVG_X+sizeof"Overall Average: ");
		printw("%.3f",over_avg);
		move(GUESS_Y, GUESS_X+sizeof"Guess: ");
		
		do{
			guess = getch();
			if(guess == '\n'){
				continue;
			}
			else if(guess == EOF){
				return 0;
			}
			else if(guess < 97 || guess > 122){
				move(WIN_OR_LOOSE_Y,WIN_OR_LOOSE_X);
				printw("\"%c\" is not a valid character", guess);
				move(GUESS_Y, GUESS_X+sizeof"Guess: ");
				continue;
			}
			else{
				int i;
				for(i=0; i<strlen(hidden_word); i++){
					if(ptr_random_word->ptr_text[i] == guess){
						hidden_word[i] = guess;
						correct=1;
					}
				}
				if(correct == 0){
					move(CURRENT_AVG_Y, CURRENT_AVG_X+sizeof"Current Average: ");
					printw("%.3f",++cur_avg/word_number);
				}
				else if(correct == 1){
					correct = 0;
				}
			}
			move(WORD_Y, WORD_X+sizeof"Word: ");
			printw("%s",hidden_word);

			if (strchr(guessed, guess) == NULL){
				strncat(guessed, (char *)&guess, 1);
				move(GUESSED_Y, GUESSED_X+sizeof"Guessed: ");
				printw("%s",guessed);
				move(GUESS_Y, GUESS_X+sizeof"Guess: ");
			}
			else{
				move(WIN_OR_LOOSE_Y,WIN_OR_LOOSE_X);
				printw("you already choose the \"%c\"", guess);
				move(GUESS_Y, GUESS_X+sizeof"Guess: ");
				continue;
			}

			if(strchr(hidden_word, guess) == NULL){
				chances--;
				mvaddch(Err_pos[Maxers].y,Err_pos[Maxers].x,Err_pos[Maxers].ch);
				Maxers++;
				move(GUESS_Y, GUESS_X+sizeof"Guess: ");
			}
		}while(strchr(hidden_word, '_') != NULL && chances > 0);
	
		if(chances > 0){
			move(WIN_OR_LOOSE_Y,WIN_OR_LOOSE_X);			
			printw("Congratulation~~~ You WIN...!!!");
			move(GUESS_Y, GUESS_X+sizeof"Guess: ");
		}
		else{
			move(WIN_OR_LOOSE_Y,WIN_OR_LOOSE_X);			
			printw("Sorry...!!! <selected word: %s>",ptr_random_word->ptr_text);
			move(GUESS_Y, GUESS_X+sizeof"Guess: ");
		}

		do{
			move(WIN_OR_LOOSE_Y+1,WIN_OR_LOOSE_X);			
			printw("if you again? [Press 'y' or 'n']:");
		 	while((answer = getch()) == '\n');
			if(answer == 'y'){
				over_avg = cur_avg/word_number;
				word_number++;
				init_screen();
				break;
			}
			else if(answer == 'n'){
				return 0;
			}
		}while(1);
		
	}while(1);
	
	return 0;
}

