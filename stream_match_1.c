#include "main.h"

/**
 * greater_than - Redirects the file descriptor to a file
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Failed if it fails or success otherwise
 */
int greater_than(general *go, char *file, int res)
{
	int fd = 0;

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		return (FAILED);
	if (dup2(fd, res) == -1)
		exit(1);
	close(fd);
	go->fd = res;
	return (SUCCESS);
}

/**
 * greater_than_x2 - Redirects the file descriptor to a file as append
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Failed if it fails or success otherwise
 */
int greater_than_x2(general *go, char *file, int res)
{
	int fd = 0;

	fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd == -1)
		return (FAILED);
	if (dup2(fd, res) == -1)
		exit(1);
	close(fd);
	go->fd = res;

	return (SUCCESS);
}

/**
 * less_than - Redirect the file descriptor to an existing file
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Failed if it fails or success otherwise
 */
int less_than(general *go, char *file, int res)
{
	int fd = 0;

	(void) go;
	fd = open(file, O_RDWR, 0666);
	if (fd == -1)
		return (FAILED);
	res = 0;
	if (dup2(fd, res) == -1)
		exit(1);
	close(fd);
	go->fd = res;
	return (SUCCESS);
}

/**
 * less_than_x2 - Creates a heredoc
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Failed if it fails or success otherwise
 */
int less_than_x2(general *go, char *file, int res)
{
	char buffer[BUFSIZ] = {0};
	char buff[BUFSIZ] = {0};
	int i = 0;
	int pipefd[2];

	(void) res;
	while (i != EOF)
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
	go->fd = STDIN_FILENO;
	write(pipefd[1], buffer, _strlen(buffer));
	close(pipefd[0]);
	close(pipefd[1]);

	return (SUCCESS);
}
