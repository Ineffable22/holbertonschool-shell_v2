#include "main.h"

/**
 * print_env - checks if environment variables will be printed
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *print_env(general *go)
{
	if (go->token[1] == NULL)
	{
		printer(go->env);
		go->res = 0;
		go->bol = 1;
		return (go);
	}
	else
	{
		printf("env: ‘%s’: No such file or directory\n", go->token[1]);
		go->bol = -1;
		go->res = 127;
		return (go);
	}
}

/**
 * who_am_i - Prints the effective user ID
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *who_am_i(general *go)
{
	envi *section = NULL;
	char *user = "USER";

	if (go->token[1] == NULL)
	{
		section = search_env(user, go->env);
		printf("%s\n", section->value);
		go->res = 0;
	}
	else
	{
		printf("whoami: extra operand ‘%s’\n", go->token[1]);
		printf("Try 'whoami --help' for more information.\n");
		go->res = 1;
	}
	go->bol = 1;
	return (go);
}

/**
 * shell_clear - Clears the terminal screen
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *shell_clear(general *go)
{
	system("clear");
	go->res = 0;
	go->bol = 1;
	return (go);
}


/**
 * change_directory - Changes the working directory
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *change_directory(general *go)
{
	char path_old[BUFSIZ] = "", path_new[BUFSIZ] = "";
	envi *section = NULL;
	int bol = 0;

	go->res = 0;
	getcwd(path_old, sizeof(path_old));
	if (go->token[1] == NULL || *go->token[1] == '~' ||
	_strcmp(go->token[1], "$HOME") == 0)
	{
		section = search_env("HOME", go->env);
		chdir(section->value);
	}
	else if (*go->token[1] == '-')
	{
		section = search_env("OLDPWD", go->env);
		chdir(section->value);
	}
	else if (chdir(go->token[1]) == -1)
	{
		errno_case(go);
		bol = 1;
		go->res = 1;
	}
	if (bol == 0)
		getcwd(path_new, sizeof(path_new));
	go->env = set_env("OLDPWD", path_old, go->env);
	go->env = set_env("PWD", path_new, go->env);
	go->bol = 1;
	return (go);
}

/**
 * errno_case - Sets and prints error
 * @go: Pointer to Structure General
 *
 * Return: Nothing
 */
void errno_case(general *go)
{
	switch (errno)
	{
	case EACCES:
		go->msg = "Permission denied";
		break;
	case ENAMETOOLONG:
		go->msg = "Path is too long";
		break;
	case ENOTDIR:
		go->msg = "No such file or directory";
		break;
	case ENOMEM:
		go->msg = "Insufficient kernel memory was available";
		break;
	case EFAULT:
		go->msg = "path points outside your accessible address space";
		break;
	case ENOENT:
		go->msg = "No such file or directory";
		break;
	}
	message_error(go, 0, NULL);
}
