#include "main.h"

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


envi *search_env(char *str, envi *env)
{
	while (env && _strcmp(env->key, str) != 0)
		env = env->next;

	return (env);
}

general *who_am_i(general *go)
{
	envi *section = NULL;
	char *user = "USER";

	if (go->token[1] == NULL)
	{
		section = search_env(user, go->env);
		printf("%s\n", section->value);
		go->res = 0;
		go->bol = 1;
		return (go);
	}
	else
	{
		printf("whoami: extra operand ‘%s’\n", go->token[1]);
		printf("Try 'whoami --help' for more information.\n");
		go->res = 1;
		go->bol = 1;
		return (go);
	}
}
general *shell_clear(general *go)
{
	(void) go->token;
	system("clear");
	go->res = 1;
	return (go);
}

general *change_directory(general *go)
{
	char path_old[BUFSIZ] = "", path_new[BUFSIZ] = "";
	envi *section = NULL;
	int bol = 0;

	go->res = 0;
	getcwd(path_old, sizeof(path_old));
	if (go->token[1] == NULL || *go->token[1] == '~' || !strcmp(go->token[1], "$HOME"))
	{
		section = search_env("HOME", go->env);
		printf("section -> %s\n", section->value);
		chdir(section->value);
	}
	else if (*go->token[1] == '-')
	{
		section = search_env("OLDPWD", go->env);
		printf("section -> %s\n", section->value);
		chdir(section->value);
	}
	else if (chdir(go->token[1]) == -1)
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
		message_error(go);
		bol = 1;
		go->res = 1;
	}
	if (bol == 0)
		getcwd(path_new, sizeof(path_new));
	printf("PWD -> %s\n", path_new);
	go->env = set_env("OLDPWD", path_old, go->env);
	go->env = set_env("PWD", path_new, go->env);
	go->bol = 1;
	return (go);
}

void message_error(general *go)
{
	if (isatty(STDIN_FILENO))
		printf("%s: cd: %s: %s\n", go->exe, go->msg, go->token[1]);
	else
		printf("%s: %d: %s: %s: %s\n", go->exe, go->n, go->token[0], go->token[1], go->msg);
}

envi *set_env(char *key, char *value, envi *env)
{
	envi *new = env;

	while (new)
	{
		if (_strcmp(new->key, key) == 0)
		{
			free(new->value);
			new->value = malloc((_strlen(value) + 1) * sizeof(char));
			_strcpy(new->value, value);
		}
		new = new->next;
	}
	return (env);
}

general *print_working_directory(general *go)
{
	envi *section = NULL;

	(void) go;

	section = search_env("PWD", go->env);
	printf("%s\n", section->value);
	go->res = 1;
	return (go);
}

general *exit_time(general *go)
{
	int num = 0;

	if (go->token[1] == NULL)
	{
		free(go->token);
		_free(go->env);
		free(go->buff);
		free(go);
		exit(0);
	}
	if (go->token[2] != NULL)
	{
		go->msg = "too many arguments";
		message_error(go);
		go->res = 1;
		go->bol = 1;
		return (go);
	}
	num = atoi(go->token[1]);
	num = (num != 0) ? num : 2;
	free(go->token);
	_free(go->env);
	free(go->buff);
	free(go);
	exit(num);
}
