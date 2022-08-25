CC = gcc
VAL = valgrind
GDB = gdb
SRC = *.c
NAME = hsh
CFLAGS = -Wall -Werror -Wextra -pedantic
GFLAGS = -g
VFLAGS = --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s

all: clean run
	./$(NAME)

run: *.h *.c
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)

rungdb: *.h *.c
	$(CC) $(SRC) $(CFLAGS) $(GFLAG) -o $(NAME)

# optional ARGS="FILENAME"
val: run
	$(VAL) $(VFLAGS) ./$(NAME) $(ARGS)

clean:
	$(RM) *~ $(NAME)
