#ifndef MAIN_H
#define MAIN_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

/* Macros */
#define SUCCESS 0
#define FAILED -1
#define FAILED_MSG -2
#define FIELD 1
#define HEREDOC 2
#define AND 1
#define OR 2

/* Checks the error type of a function */
extern int errno;

/* Structures */

/**
 * struct General - Is a Struct with all general utility commands
 * to evaluate at each momment of the program
 * @std_in: Standar Input
 * @std_out: Standar Output
 * @exe: Executable program name
 * @n: Number of commands inserts
 * @buff: Pointer to buffer
 * @token: Pointer to tokens
 * @res: Status Code Result
 * @bol: Bolean
 * @msg: Error message
 * @fd: Saves file descriptor or pipe[0]
 * @fd1: Saves pipe[1]
 * @field: Sets where a field ends
 * @end: Reports if commands finished
 * @is_file: Reports if it's reading a file
 * @operator: Logical operator AND - OR
 * @PS1: Saves the custom prompt
 * @env: Pointer to Struture Envi
 * @tkn: Pointer to Struture Tokens
 */
typedef struct General
{
	int std_in;
	int std_out;
	char *exe;
	int n;
	char *buff;
	char **token;
	int res;
	int bol;
	char *msg;
	int fd;
	int fd1;
	char *field;
	int end;
	int is_file;
	int operator;
	char *PS1;
	struct Envi *env;
	struct Tokens *tkn;
} general;

/**
 * struct Tokens - Singly linked list
 * @token: Points to the token
 * @next: Points to the next node
 * Description: Singly linked list of tokens
 */
typedef struct Tokens
{
	char *token;
	struct Tokens *next;
} tokens;

/**
 * struct Envi - Singly linked list
 * @key: Points to the key of the environment variable
 * @value: Points to the value of the environment variable
 * @next: Points to the next node
 * Description: Singly linked list of the environment variables
 */
typedef struct Envi
{
	char *key;
	char *value;
	struct Envi *next;
} envi;

/**
 * struct Cmd - Function pointer
 * @c: String to compare
 * @f: Function to execute
 * Description: function pointer structure to send a function
 * if it matches the string
 * Match shell commands
 */
typedef struct Cmd
{
	char *c;

	general *(*f)(general *);
} cmd;

/**
 * struct Lexers - Function pointer
 * @c: String to compare
 * @f: Function to execute
 * Description: function pointer structure to send a function
 * if it matches the string
 * Match Lexers
 */
typedef struct Lexers
{
	char *c;
	int (*f)(general *, char *, int);
} lexers;

/* Prototypes */

/*_____main.c_____*/
void response_signal(int x);
envi *reload_env(char **enviroment, envi *envi);
envi *add_node(char *enviroment, envi *env);
void prompt(char *p, general *go);


/*_____bypass.c_____*/
general *go_bypass(general *go, char *buffer);
general *validate_stream(general *go);
char *is_var(envi *env, char *buffer, int res);
tokens *add_token(tokens **token, char *buffer);
void add_history(general *buff);

/*_____free_fd.c_____*/
general *_free_fd(general *go);
int _atoi(char *str, int *res);
general *check_parent(general *go, int status);

/*_____special_functions.c_____*/
envi *search_env(char *str, envi *env);
envi *set_env(char *key, char *value, envi *env);
void precmd(general *go, char *file);
general *history(general *go);
general *help(general *go);

/*_____built_in_1.c_____*/
general *print_env(general *go);
general *who_am_i(general *go);
general *change_directory(general *go);
int middle_dash(general *go, int bol, char *path_old);
void errno_case(general *go);

/*_____built_in_2.c_____*/
general *shell_clear(general *go);
general *print_working_directory(general *go);
general *exit_time(general *go);
general *shell_setenv(general *go);
general *shell_unsetenv(general *go);

/*_____built_in_3.c_____*/
general *PS1(general *go);
general *alias(general *go);

/*_____final_functions.c_____*/
general *built_in(general *go);
int stream_match(general *go, tokens *tk, char *exe);
int functions_bin(general *go);
char **get_env(envi *env, char **environ);
char *_access(char *token, envi *env);

/*_____stream_match_1.c_____*/
int greater_than(general *go, char *file, int res);
int greater_than_x2(general *go, char *file, int res);
int less_than(general *go, char *file, int res);
int less_than_x2(general *go, char *file, int res);

/*_____stream_match_2.c_____*/
int pipe_mode(general *go, char *file, int res);
int semicolon(general *go, char *file, int res);
int ampersand(general *go, char *file, int res);
int double_pipe(general *go, char *file, int res);
int hash(general *go, char *file, int res);

/*_____utilities.c_____*/
void printer(envi *env);
void _free_env(envi *env, char *PS1);
void _free_tkn(tokens *token);
void _free_double(char **token);
void message_error(general *go, char val, char *tok);

/*_____holbie_tools.c_____*/
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strlen2(char **s);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);

/*_____holbie_tools2.c_____*/
int _strncmp(char *s1, char *s2, int n);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_realloc(char *ptr, unsigned int size);
int _lexers_cmp(char *s1, char *s2, int i);
char *itoa(int val, int base);

#endif
