#include "main.h"
#include "_getline.h"

/**
 * search_env - Searchs an environment variable
 * @str: String to compare
 * @env: Pointer to Singly linked list with the environment variables
 *
 * Return: Pointer to an environment variable or NULL otherwise
 */
envi *search_env(char *str, envi *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (!env->key)
			return (NULL);
		if (_strcmp(env->key, str) == 0)
			break;
		env = env->next;
	}
	return (env);
}

/**
 * set_env - Set a value in the Singly linked list Envi
 * @key: Key to insert
 * @value: Value to insert
 * @env: Pointer to Singly linked list with the environment variables
 *
 * Return: Pointer to the singly linked list with the new or
 * replaced environment variable
 */
envi *set_env(char *key, char *value, envi *env)
{
	envi *new = env, *prev = NULL;
	int bol = 0;

	if (env == NULL)
	{
		env = _calloc(1, sizeof(envi));
		env->key = _calloc((_strlen(key) + 1), sizeof(char));
		_strcpy(env->key, key);

		env->value = _calloc((_strlen(value) + 1), sizeof(char));
		_strcpy(env->value, value);
	}
	else
	{
		while (new)
		{

			if (_strcmp(new->key, key) == 0)
			{
				free(new->value);
				new->value = malloc((_strlen(value) + 1) * sizeof(char));
				_strcpy(new->value, value);
				bol = 1;
			}
			prev = new;
			new = new->next;
		}
		if (bol == 0)
		{
			prev->next = _calloc(1, sizeof(envi));
			prev->next->key = _calloc((_strlen(key) + 1), sizeof(char));
			_strcpy(prev->next->key, key);

			prev->next->value = _calloc((_strlen(value) + 1), sizeof(char));
			_strcpy(prev->next->value, value);
		}
	}
	return (env);
}

/**
 * precmd - Executes the commands contained in the file line per line
 * @go: Pointer to Structure General
 * @file: Pointer with the name of the file to evaluate
 *
 * Return: Nothing
 */
void precmd(general *go, char *file)
{
	int fd = 0;
	char *line = NULL;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return;

	while ((line = _getline(fd)) != NULL)
	{
		if (_strlen(line) != 0)
			go = go_bypass(go, line);
		free(line);
	}
	close(fd);
	_getline(-1);
}

/**
 * history - Prints the command history
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *history(general *go)
{
	int fd = 0, digit = 1, k = 0;
	envi *section = NULL;
	char *file = NULL;
	char *name = "/.hsh_history";
	char *line = NULL;

	section = search_env("HOME", go->env);
	file = malloc((_strlen(name) + _strlen(section->value) + 1) * sizeof(char));
	_strcpy(file, section->value);
	_strcpy(&file[_strlen(section->value)], name);

	fd = open(file, O_CREAT | O_RDONLY, 0666);
	if (fd == -1)
		exit(-1);
	free(file);

	while ((line = _getline(fd)) != NULL)
	{
		for (k = 10000; k > digit; k /= 10)
			putchar(32);
		printf("%d", digit);
		putchar(32);
		putchar(32);
		printf("%s\n", line);
		free(line);
		digit++;
	}
	close(fd);
	_getline(-1);
	go->res = 0;
	go->bol = 1;
	return (go);
}

/**
 * help - Prints the help manual
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *help(general *go)
{
	char *line = NULL;
	int fd = 0;
	char bol = 0;

	if (go->token[1] == NULL)
		fd = open("help/help", O_RDONLY);
	else if (_strcmp(go->token[1], "cd") == 0)
		fd = open("help/help_cd", O_RDONLY);
	else if (_strcmp(go->token[1], "help") == 0)
		fd = open("help/help_help", O_RDONLY);
	else if (_strcmp(go->token[1], "history") == 0)
		fd = open("help/help_history", O_RDONLY);
	else
	{
		printf("-bash: help: no help topics match `%s'.", go->token[1]);
		printf("  Try `help help' or `man -k %s'", go->token[1]);
		printf(" or `info %s'.\n", go->token[1]);
		bol = 1;
		go->res = 1;
	}
	if (bol != 1)
	{
		while ((line = _getline(fd)) != NULL)
		{
			printf("%s\n", line);
			free(line);
		}
		close(fd);
		_getline(-1);
		go->res = 0;
	}
	go->bol = 1;
	return (go);
}
