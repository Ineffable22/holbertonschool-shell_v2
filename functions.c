#include "main.h"

general * go_bypass(general *go, char *buffer, int size)
{
	int i = 0;

	go->bol = 0;
	go->buff = buffer;
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
	if (go->bol == 0)
		go->bol = functions_bin(go);
	if (go->bol == 0)
	{
		go->res = (go->res == 0) ? 127 : 2;
		if (isatty(STDIN_FILENO))
			printf("%s: command not found\n", go->token[0]);
		else
		{
			if (go->res == 2)
				printf("%s: %d: '%s %s %s'\n", go->exe, go->n, go->token[0], go->token[1], go->token[2]);
			else
				printf("%s: %d: %s: not found\n", go->exe, go->n, go->token[0]);
		}
	}
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

int validate_stream(general *go)
{
	int i = 0, res = 0;

	while (go->token[i])
	{
		res = stream_match(go->token[i], go->token[i + 1], go->exe);
		if (res == 1)
			return (i);
		if (res == -1)
		{
			go->res = 2;
			return (-1);
		}
		if (res == 3)
		{
			go->fd = res;
			return (i);
		}
		i++;
	}
	return (0);
}

int functions_bin(general *go)
{
	pid_t child = 0;
	int status = 0, res = -1;
	char *path = NULL;
	char **token = NULL;

	if ((path = _access(go->token[0], go->env)) == NULL)
		return (0);

	child = fork();
	if (child == 0)
	{
		res = validate_stream(go);
		if (res == -1)
		{
			go->res = 2;
			return (0);
		}
		
		if (res == 0)
			execve(path, go->token, environ);
		else
			execve(path, _strncpy2(token, go->token, res), environ);
		
		kill(getpid(), SIGKILL);
	}
	else if (child > 0)
	{
		/*write(go->fd, buffa, 10);*/
		
		wait(&status);
	}
	free(path);
	if (token)
		free(token);
	go->res = 0;
	return (1);
}
