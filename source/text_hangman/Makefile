TARGET = built-in.o
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
CFLAGS = -I../../include
CFLAGS += -lcurses

all : $(OBJECTS)
	$(LD) -r $(OBJECTS) -o $(TARGET)

clean :
	rm -rf *.o $(TARGET)


