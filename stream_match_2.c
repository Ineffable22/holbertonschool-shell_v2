#include "main.h"

/**
 * pipe_mode - Creates a pipe
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Exit if it fails or field otherwise
 */
int pipe_mode(general *go, char *file, int res)
{
	int pipefd[2];

	(void) file;
	(void) res;

	go->std_out = dup(STDOUT_FILENO);
	if (pipe(pipefd) == -1)
		exit(1);
	go->fd = pipefd[0];
	go->fd1 = pipefd[1];
	if (dup2(go->fd1, STDOUT_FILENO) == -1)
		exit(1);
	close(go->fd1);

	return (FIELD);
}

/**
 * semicolon - Just assigns a field to receive another command
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Field always
 */
int semicolon(general *go, char *file, int res)
{
	(void) go;
	(void) file;
	(void) res;

	return (FIELD);
}

/**
 * ampersand - Gets an AND operator and terminate execution if it fails
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Field always
 */
int ampersand(general *go, char *file, int res)
{
	(void) file;
	(void) res;

	go->operator = AND;
	return (FIELD);
}

/**
 * double_pipe - Gets an OR operator and terminate execution if it success
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Field always
 */
int double_pipe(general *go, char *file, int res)
{
	(void) file;
	(void) res;

	go->operator = OR;
	return (FIELD);
}

/**
 * hash - Simply assigns a field and specify the end
 * to ignore the following commands
 * @go: Pointer to Structure General
 * @file: Name of file or key
 * @res: File Descriptor Result
 *
 * Return: Field always
 */
int hash(general *go, char *file, int res)
{
	(void) file;
	(void) res;

	go->end = 1;
	return (FIELD);
}
