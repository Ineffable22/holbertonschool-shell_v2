CC = gcc
VAL = valgrind
GDB = gdb
SRC = *.c
NAME = hls
CFLAGS = -Wall -Werror -Wextra -pedantic -g
VFLAGS = --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s

all: clean run val

run: *.h *.c
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)

# optional ARGS="FILENAME"
val: run
	$(VAL) $(VFLAGS) ./$(NAME) $(ARGS)

gdb: run
	$(GDB) ./$(NAME)

clean:
	$(RM) *~ $(NAME)
