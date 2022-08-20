#include "main.h"

general *go_match(general *go)
{
	int i = 0, res = 0;
	cmd flag_store[] = {
		{"env", print_env},
		{"whoami", who_am_i},
		{"clear", shell_clear},
		{"cd", change_directory},
		{"pwd", print_working_directory},
		{"exit", exit_time},
		{NULL, NULL}
	};

	for (i = 0; flag_store[i].c; i++)
	{
		res = strcmp(go->token[0], flag_store[i].c);
		if (res == 0)
		{
			go = flag_store[i].f(go);
			return (go);
		}
	}
	go->res = 0;
	return (go);
}


int stream_match(char *symbol, char *file, char *exe)
{
	int i = 0, res = 0;
	advance flag_store[] = {
		{">", greater_than},
		{">>", greater_than_x2},
		{"<", less_than},
		{"<<", less_than_x2},
		{NULL, NULL}
	};

	for (i = 0; flag_store[i].c; i++)
	{
		res = _lexers_cmp(symbol, flag_store[i].c);
		if (res > 0 && res < 10)
		{
			if (file == NULL)
			{
				printf("%s: syntax error near unexpected token `newline'\n", exe);
				return (-1);
			}
			else
				res = flag_store[i].f(file, res);
			return (res);
		}
	}
	return (0);
}

int greater_than(char *file, int res)
{
	int fd = 0;

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		return (-1);
	dup2(fd, res);
	close(fd);
	return (1);
}

int greater_than_x2(char *file, int res)
{
	int fd = 0;

	fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd == -1)
		return (-1);
	dup2(fd, res);
	close(fd);
	return (1);
}

int less_than(char *file, int res)
{
	int fd = 0;

	fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd == -1)
		return (-1);
	res = 0;
	dup2(fd, res);
	close(fd);
	return (1);
}


int less_than_x2(char *file, int res)
{
	char buffer[BUFSIZ] = {0};
	char buff[BUFSIZ] = {0};
	int i = 0;
	int pipefd[2];
	
	while(i != EOF)
	{
		i = read(0, &buff[_strlen(buff)], BUFSIZ);
		if (_strcmp(&buff[_strlen(buff) - i], file) == 10)
			break;
	}
	_strncpy(buffer, buff, _strlen(buff) - i);
	if (pipe(pipefd) == -1)
		exit(1);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit(1);
	write(pipefd[1], buffer, _strlen(buffer));
	close(pipefd[0]);
	close(pipefd[1]);
	return (res);
}
