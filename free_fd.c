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
