#include "main.h"

/**/
int main(int argc, char **argv, char **enviroment)
{
	struct General *go = NULL;
	int i = 0;
	char *buffer = NULL;
	size_t size = 0;
	char *user = "#Cisfun";

	(void) argc;
	(void) argv;
	errno = 0;

	signal(SIGINT, response_signal);
	go = _calloc(1, sizeof(general));
	if (go == NULL)
		return (-1);
	go->exe = argv[0];
	go->env = NULL;
	go->env = reload_env(enviroment, go->env);
	if (go->env == NULL)
		return (-1);
	while(i != EOF)
	{
		go->n += 1;
		if (isatty(STDIN_FILENO))
			prompt(user, go);
		i = getline(&buffer, &size, stdin);
		/*printf("Buffer -> %s\t response -> %d\n", buffer, i);*/
		if (i > 1)
		{
			go = go_bypass(go, buffer, i);
		}
	}
	i = go->res;
	_free(go->env);
	free(go);
	free(buffer);
	return (i);
}

void prompt(char *p, general *go)
{
	envi *home = search_env("HOME", go->env);
	envi *path = search_env("PWD", go->env);
	int len = strlen(home->value);

	if (_strncmp(path->value, home->value, len) == 1)
		printf("%s:~%s$ ", p, &path->value[len]);
	else
		printf("%s:%s$ ", p, path->value);
}

void response_signal(int x)
{
	(void) x;
	write(1, "\n#Cisfun:~$ ", 10);
}

envi *reload_env(char **enviroment, envi *env)
{
	int i = 0;

	for (; enviroment[i]; i++)
	{
		env = add_node(enviroment[i], env);
	}
	return (env);
}

envi *add_node(char *enviroment, envi *env)
{
	envi *node = NULL, *tmp = env;
	int i = 0;

	node = _calloc(1, sizeof(envi));
	for(i = 0; enviroment[i] != '='; i++)
	{}

	node->key = _calloc((i + 1), sizeof(char));
	_strncpy(node->key, enviroment, i);

	node->value = _calloc((_strlen(enviroment) - i), sizeof(char));
	_strcpy(node->value, &(enviroment[i + 1]));

	if (env == NULL)
		return (node);

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (env);
}
