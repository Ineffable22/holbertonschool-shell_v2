#include "main.h"

general *print_env(general *go)
{
	if (go->token[1] == NULL)
	{
		printer(go->env);
		go->res = 1;
		return (go);
	}
	else
	{
		printf("env: ‘%s’: No such file or directory\n", go->token[1]);
		go->res = -1;
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
		go->res = 1;
		return (go);
	}
	else
	{
		printf("whoami: extra operand ‘%s’\n", go->token[1]);
		printf("Try 'whoami --help' for more information.\n");
		go->res = -1;
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
		printf("-bash: cd: %s: No such file or directory\n", go->token[1]);
		bol = 1;
	}
	if (bol == 0)
		getcwd(path_new, sizeof(path_new));
	go->env = set_env("OLDPWD", path_old, go->env);
	go->env = set_env("PWD", path_new, go->env);
	go->res = 1;
	return (go);
}

envi *set_env(char *key, char *value, envi *env)
{
	envi *new = env;

	while (new)
	{
		if (_strstr(new->key, key) == 1)
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
