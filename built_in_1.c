#include "main.h"

/**
 * print_env - checks if environment variables will be printed
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *print_env(general *go)
{
	if (!go->env)
	{
		go->msg = "No such file or directory";
		message_error(go, 0, NULL);
		go->res = 127;
		go->bol = 1;
		return (go);
	}
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

	go->bol = 1;
	if (go->token[1] == NULL)
	{
		section = search_env(user, go->env);
		if (section == NULL)
		{
			go->res = 0;
			go->bol = 0;
		}
		else
		{
			printf("%s\n", section->value);
			go->res = 0;
		}
	}
	else
	{
		printf("whoami: extra operand ‘%s’\n", go->token[1]);
		printf("Try 'whoami --help' for more information.\n");
		go->res = 1;
	}
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

	go->bol = 1, getcwd(path_old, BUFSIZ);
	if (go->token[1] == NULL || _strcmp(go->token[1], "$HOME") == 0 ||
	_strcmp(go->token[1], "--") == 0)
	{
		section = search_env("HOME", go->env);
		if (section == NULL)
		{
			go->msg = "HOME not set";
			message_error(go, 0, NULL);
			bol = 1;
		}
		else
			chdir(section->value);
	}
	else if (_strcmp(go->token[1], "~") == 0)
	{
		section = search_env("HOME", go->env);
		if (section == NULL)
			section = search_env("OLDPWD", go->env);
		chdir(section ? section->value : path_old);
	}
	else if ((go->token[1])[0] == '-')
	{
		bol = middle_dash(go, bol, path_old);
	}
	else if (chdir(go->token[1]) == -1)
		errno_case(go), bol = 1, go->res = 1;
	if (bol == 0)
	{
		getcwd(path_new, BUFSIZ);
		go->env = set_env("OLDPWD", path_old, go->env);
		go->env = set_env("PWD", path_new, go->env);
	}
	return (go);
}

/**
 * middle_dash - middle dash option
 * @go: Pointer to Structure General
 * @bol: bolean to validate
 * @path_old: old pwd
 *
 * Return: Pointer to Structure General
 */
int middle_dash(general *go, int bol, char *path_old)
{
	envi *section = NULL;

	if ((go->token[1])[1])
	{
		printf("%s: %d: cd: -%c: invalid option\n",
		go->exe, go->n, (go->token[1])[1]);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		go->res = 2, bol = 1;
	}
	else
	{
		section = search_env("OLDPWD", go->env);
		if (section == NULL)
		{
			go->msg = "OLDPWD not set";
			message_error(go, 0, NULL);
			bol = 1;
		}
		else
		{
			if (!isatty(STDIN_FILENO))
				printf("%s\n", section ? section->value : path_old);
			chdir(section->value);
		}
	}
	return (bol);
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
		go->msg = "Not a directory";
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
