#include "main.h"

general * go_bypass(general *go, char *buffer, int size)
{
	int i = 0;

	go->token = malloc(sizeof(char *) * size);
	if (go->token == NULL)
	{
		fprintf(stderr, "Can't malloc\n");
		return (NULL);
	}

	while((go->token[i] = strtok(buffer, " \t\n")) != NULL)
	{
		buffer = NULL;
		i++;
	}

	go = go_match(go);
	if (go->res == 0)
		go->res = functions_bin(go);
	if (go->res == 0)
		printf("%s: command not found\n", go->token[0]);
	free(go->token);
	return (go);
}

char *_access(char *token, envi *env)
{
	envi *section = NULL;
	int start = 0, end = 0, len = _strlen(token);
	char *exe = NULL;
	char *file = NULL;

	section = search_env("PATH", env);
	file = _calloc(len + 2, sizeof(char));
	_strcpy(file, "/");
	_strcpy(&file[1], token);
	len = _strlen(file);
	for (end = 0; section->value[end]; end++)
	{
		if (section->value[end] == ':')
		{
			exe = _calloc(len + (end - start) + 1, sizeof(char));
			_strncpy(exe, &section->value[start], end - start);
			_strcpy(&exe[end - start], file);
			if (access(exe, X_OK) == 0)
			{
				free(file);
				return (exe);
			}
			free(exe);
			start = end;
			start ++;
		}
	}
	free(file);
	return (NULL);
}

int functions_bin(general *go)
{
	pid_t child = 0;
	int status = 0;
	char *path = NULL;

	if ((path = _access(go->token[0], go->env)) == NULL)
		return (0);

	child = fork();
	if (child == 0)
	{
		execve(path, go->token, environ);
		kill(getpid(), SIGKILL);
	}
	else if (child > 0)
	{
		wait(&status);
	}
	free(path);
	return (1);
}
