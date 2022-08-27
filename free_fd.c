#include "main.h"

/**
 * _free_fd - Creates dups and closes file descriptors.
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *_free_fd(general *go)
{
	if (go->std_out > 2 && go->fd == -1)
	{
		if (dup2(go->std_in, STDIN_FILENO) == -1)
			exit(1);
		close(go->std_in);
		go->std_in = -1;
		go->std_out = -1;
	}
	if (go->fd >= 0)
	{
		if (go->fd1 >= 0)
		{
			go->std_in = dup(STDIN_FILENO);
			if (dup2(go->fd, STDIN_FILENO) == -1)
				exit(1);
			close(go->fd);

			if (dup2(go->std_out, STDOUT_FILENO) == -1)
				exit(1);
			close(go->std_out);
			go->fd = -1;
			go->fd1 = -1;
		}
		else
		{
			go->std_in = dup(STDIN_FILENO);
			if (go->fd >= 0)
				close(go->fd);
			if (go->fd == 1)
				go->std_in = dup(STDIN_FILENO);
			if (go->fd == 0)
				go->std_out = dup(STDOUT_FILENO);
			go->fd = -1;
		}
	}
	return (go);
}

/**
 * _atoi - Converts a string to a number
 * @str: String to convert
 * @res: Status code result
 *
 * Return: Number
 */
int _atoi(char *str, int *res)
{
	int i = 0, j = 1;
	int abs = 1, zero = 0;
	int num = 0;

	if (str[0] == '-')
	{
		if (str[1] == '-' && !str[2])
			return (num);
		else if (str[1])
		{
			abs = -1;
			zero++;
		}
	}
	for (i = _strlen(str) - 1; i >= zero; i--)
	{
		if (str[i] - 48 < 0 || str[i] - 48 > 9)
		{
			(*res) = 2;
			return (-1);
		}
		num += (str[i] - 48) * j;
		if (j == 1)
			j = 10;
		else
			j *= 10;
	}
	return (num * abs);
}

/**
 * check_parent - Checks status code
 * @go: Pointer to Structure General
 * @status: Number to check
 *
 * Return: Pointer to Structure General
 */
general *check_parent(general *go, int status)
{
	if (status != 0) /* signal-safety  */
	{
		go->res = WEXITSTATUS(status);/* fault state */
		if (go->operator == AND)
			go->end = 1;
		if (go->res == 126)
		{
			go->msg = "Permission denied";
			message_error(go, 2, NULL);
		}
	}
	else
	{
		if (go->operator == OR)
			go->end = 1;
	}
	return (go);
}
