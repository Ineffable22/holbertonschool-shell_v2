CC = gcc
VAL = valgrind
GDB = gdb
BETTY = betty
SRC = *.c
HEADER = *.h
NAME = hsh
CFLAGS = -Wall -Werror -Wextra -pedantic
GFLAG = -g
VFLAGS = --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s

all: clean run
	./$(NAME)

run: *.h *.c
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)

rungdb: *.h *.c
	$(CC) $(SRC) $(CFLAGS) $(GFLAG) -o $(NAME)
	$(GDB) $(NAME)

# optional ARGS="FILENAME"
val: run
	$(VAL) $(VFLAGS) ./$(NAME) $(ARGS)

betty:
	$(BETTY) $(SRC) $(HEADER)

clean:
	$(RM) *~ $(NAME)
