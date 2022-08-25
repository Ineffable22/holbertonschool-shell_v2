#include "main.h"

/**
 * main - Principal funcion of The Gates of Shell
 * @argc: Number of arguments
 * @argv: pointer to arguments
 * @enviroment: Content of environment variables
 *
 * Return: Status code
 */
int main(int argc, char **argv, char **enviroment)
{
	struct General *go = NULL;
	int i = 0;
	char *buffer = NULL;
	size_t size = 0;
	char *user = "#Cisfun";

	(void) argc;
	errno = 0;

	signal(SIGINT, response_signal);
	go = _calloc(1, sizeof(general));
	if (go == NULL)
		return (-1);
	go->exe = argv[0], go->PS1 = NULL;
	go->env = NULL, go->res = 0, go->is_file = 1;
	go->env = reload_env(enviroment, go->env);
	if (go->env == NULL)
		return (-1);
	if (argv[1])
		precmd(go, argv[1]);
	go->is_file = 0;
	while (i != EOF)
	{
		go->n += 1;
		if (isatty(STDIN_FILENO))
			prompt(user, go);
		i = getline(&buffer, &size, stdin);
		if (i > 1)
			go = go_bypass(go, buffer);
	}
	i = go->res;
	_free_env(go->env, go->PS1);
	free(go);
	free(buffer);
	return (i);
}

/**
 * response_signal - Prints the prompt signal (Ctrl + C)
 * @x: Unused number
 *
 * Return: Nothing
 */
void response_signal(int x)
{
	(void) x;
	write(1, "\n#Cisfun:~$ ", 10);
}

/**
 * reload_env - Saves the environment variables in the singly linked list Envi
 * @enviroment: Content of environment variables
 * @env: Pointer to Singly linked list with the environment variables
 *
 * Return: Singly linked list with the environment variables
 */
envi *reload_env(char **enviroment, envi *env)
{
	int i = 0;

	for (; enviroment[i]; i++)
		env = add_node(enviroment[i], env);
	return (env);
}


/**
 * prompt - Prints the prompt
 * @p: Current working directory
 * @go: Pointer to Structure General
 *
 * Return: Nothing
 */
void prompt(char *p, general *go)
{
	envi *home = search_env("HOME", go->env);
	envi *path = NULL;
	int len = _strlen(home->value);

	if (go->PS1 == NULL)
	{
		path = search_env("PWD", go->env);
		if (_strncmp(path->value, home->value, len) == 1)
			printf("%s:~%s$ ", p, &path->value[len]);
		else
			printf("%s:%s$ ", p, path->value);
	}
	else
	{
			printf("%s$ ", go->PS1);
	}
}




/**
 * add_node - Saves an environment variable in a node
 * @enviroment: Content of an environment variable
 * @env: Pointer to Singly linked list with the environment variables
 *
 * Return: Singly linked list with new environment variables node
 */
envi *add_node(char *enviroment, envi *env)
{
	envi *node = NULL, *tmp = env;
	int i = 0;

	node = _calloc(1, sizeof(envi));
	for (i = 0; enviroment[i] != '='; i++)
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
