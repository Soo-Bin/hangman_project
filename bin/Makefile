TARGET = hangman
SUBDIRS = ../source/text_hangman\
		  ../source/main

OBJECTS = ../source/text_hangman/built-in.o\
		  ../source/main/built-in.o
CFLAGS = -lcurses

export CC = gcc

all : compile $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

compile :
	@for dir in $(SUBDIRS); do \
	make -C $$dir || exit $?; \
	done

clean :
	@for dir in $(SUBDIRS); do \
	make -C $$dir clean; \
	done
	rm -rf *.o $(TARGET)


