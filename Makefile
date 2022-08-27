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

all: clean *.h *.c
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)
run: 
	./$(NAME)

rungdb: *.h *.c
	$(CC) $(SRC) $(CFLAGS) $(GFLAG) -o $(NAME)
	$(GDB) $(NAME)

# optional ARGS="FILENAME"
val: all
	$(VAL) $(VFLAGS) ./$(NAME) $(ARGS)

betty:
	$(BETTY) $(SRC) $(HEADER)

clean:
	$(RM) *~ $(NAME)
