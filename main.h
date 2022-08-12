#ifndef MAIN_H
#define MAIN_H

/* Libraries  */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/* Structures */

typedef struct General
{
	char **token;
	struct Envi *env;
	int res;
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

/*_____ _____*/
/* Prototypes */

/*_____main.c_____*/
void response_signal(int x);
envi *reload_env(char **enviroment, envi *envi);
envi *add_node(char *enviroment, envi *env);

/*_____go_match.c_____*/
general *go_match(general *go);

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

/*_____utilities.c_____*/
void printer(envi *env);
void _free(envi *env);
void _free2(char **env);

/*_____holbie_tools.c_____*/
int _strstr(char *s1, char *s2);
int _strlen(char *s);
int _strlen2(char **s);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_realloc(char *ptr, unsigned int size);
int _strcmp(char *s1, char *s2);

#endif
