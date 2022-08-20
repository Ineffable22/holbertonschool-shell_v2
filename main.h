#ifndef MAIN_H
#define MAIN_H

/* Libraries  */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

extern char **environ;
extern errno;

/* Structures */

typedef struct General
{
	char *exe;
	int n;
	char *buff;
	char **token;
	struct Envi *env;
	int res;
	int bol;
	char *msg;
	int fd;
} general;

typedef struct Envi
{
	char *key;
	char *value;
	struct Envi *next;
} envi;

typedef struct Cmd {
	char *c;
	general *(*f)(general *);
} cmd;

typedef struct Advance {
	char *c;
	int (*f)(char *, int);
} advance;

/*_____ _____*/
/* Prototypes */

/*_____main.c_____*/
void response_signal(int x);
envi *reload_env(char **enviroment, envi *envi);
envi *add_node(char *enviroment, envi *env);
void prompt(char *p, general *go);

/*_____go_match.c_____*/
general *go_match(general *go);
int stream_match(char *symbol, char *file, char *exe);
int greater_than(char *file, int res);
int greater_than_x2(char *file, int res);
int less_than(char *file, int res);
int less_than_x2(char *file, int res);

/*_____functions.c_____*/
general *go_bypass(general *go, char *buffer, int size);
int functions_bin(general *go);
char *_access(char *token, envi *env);

/* functions_match */
general *print_env(general *go);
general *who_am_i(general *go);
general *change_directory(general *go);
envi *search_env(char *str, envi *env);
general *shell_clear(general *go);
general *print_working_directory(general *go);
envi *set_env(char *key, char *value, envi *env);
general *exit_time(general *go);
void message_error(general *go);

/*_____utilities.c_____*/
void printer(envi *env);
void _free(envi *env);
void free_section(char **token, int res);

/*_____holbie_tools.c_____*/
int _strstr(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
int _strlen(char *s);
int _strlen2(char **s);
char *_strcpy(char *dest, char *src);
char **_strncpy2(char **dest, char **src, int n);
char *_strncpy(char *dest, char *src, int n);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_realloc(char *ptr, unsigned int size);
int _strcmp(char *s1, char *s2);
int _lexers_cmp(char *s1, char *s2);

#endif
