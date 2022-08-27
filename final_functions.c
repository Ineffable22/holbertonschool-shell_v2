#include "main.h"

/**
 * built_in - Checks if matches with the value of the pointer to structure
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *built_in(general *go)
{
	int i = 0, res = 0;
	cmd flag_store[] = {
		{"env", print_env},
		{"whoami", who_am_i},
		{"clear", shell_clear},
		{"cd", change_directory},
		{"pwd", print_working_directory},
		{"exit", exit_time},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"history", history},
		{"help", help},
		{"alias", alias},
		{"PS1", PS1},
		{NULL, NULL}
	};

	for (i = 0; flag_store[i].c; i++)
	{
		res = _strcmp(go->token[0], flag_store[i].c);
		if (res == 0)
		{
			go = flag_store[i].f(go);
			return (go);
		}
	}
	go->res = 0;
	return (go);
}

/**
 * stream_match - Checks if matches with the value of the pointer to structure
 * @go: Pointer to Structure General
 * @tk: Pointer to Structure Tokens
 * @exe: Name of the executable program
 *
 * Return: Failed if it fails or success otherwise
 */
int stream_match(general *go, tokens *tk, char *exe)
{
	int i = 0, fd = 0, res = 0;
	lexers flag_store[] = {
		{">", greater_than},
		{">>", greater_than_x2},
		{"<", less_than},
		{"<<", less_than_x2},
		{"|", pipe_mode},
		{";", semicolon},
		{"&&", ampersand},
		{"||", double_pipe},
		{"#", hash},
		{NULL, NULL}
	};

	for (i = 0; flag_store[i].c; i++)
	{
		fd = _lexers_cmp(tk->token, flag_store[i].c, i);
		if (fd >= 0 && fd < 10)
		{
			if (tk->next == NULL && *flag_store[i].c != '#')
			{
				printf("%s: syntax error near unexpected token `newline'\n", exe);
				go->res = 2;
				go->end = 1;
				return (FAILED_MSG);
			}
			else if (tk->next)
				res = flag_store[i].f(go, tk->next->token, fd);
			if (res == FAILED)
			{
				message_error(go, 1, tk->next->token);
				go->res = 1;
				go->end = 1;
			}
			return (res);
		}
	}
	return (10);
}

/**
 * functions_bin - Creates a fork and send a command to run
 * @go: Pointer to Structure General
 *
 * Return: 1 is success or exit otherwise
 */
int functions_bin(general *go)
{
	pid_t child = 0;
	int status = 0;
	char *path = NULL, **env = NULL;

	go->res = 0;
	path = _access(go->token[0], go->env);
	if (path == NULL)
		return (0);

	env = get_env(go->env, env);
	child = fork();
	if (child == -1)
		perror("An Error ocurred with Fork\n");
	else if (child == 0)
	{
		if (execve(path, go->token, env) == -1)
		{
			if (errno == EACCES)
				exit(126);
			_exit(1);
		}
		kill(getpid(), SIGKILL);
	}
	else
	{
		wait(&status);
		go = check_parent(go, status);
	}
	_free_double(env);
	if (_strcmp(go->token[0], path) != 0)
		free(path);
	return (1);
}

/**
 * get_env - Create a double pointer with the environment variables
 * @env: Pointer to Singly linked list with the environment variables
 * @environ: Double pointer to store
 *
 * Return: Double pointer with the environment variables
 */
char **get_env(envi *env, char **environ)
{
	envi *tmp = env;
	int i = 0, lenk = 0, lenv = 0, len_env = 0;

	for (; tmp; tmp = tmp->next)
		len_env++;
	environ = _calloc(len_env + 1, sizeof(char *));
	while (env)
	{
		lenk = _strlen(env->key);
		lenv = _strlen(env->value);
		environ[i] = malloc((lenk + lenv + 2) * sizeof(char));
		_strcpy(environ[i], env->key);
		_strcpy(&environ[i][lenk], "=");
		_strcpy(&environ[i][lenk + 1], env->value);
		env = env->next;
		i++;
	}
	return (environ);
}

/**
 * _access - Checks if the command exist in the PATH
 * @token: Pointer to Singly linked list with the tokens
 * @env: Pointer to Singly linked list with the environment variables
 *
 * Return: The PATH or NULL otherwise
 */
char *_access(char *token, envi *env)
{
	envi *section = NULL;
	int start = 0, end = 0, bol = 0, len = _strlen(token);
	char *exe = NULL;
	char *file = NULL;

	if (token[0] == '.')
	{
		if (!token[1] || (token[1] == '.' && !token[2]))
			return (NULL);
	}
	if (access(token, F_OK) == 0)
		return (token);
	section = search_env("PATH", env);
	if (section == NULL)
		return (NULL);
	file = _calloc(len + 2, sizeof(char));
	_strcpy(file, "/");
	_strcpy(&file[1], token);
	len = _strlen(file);
	for (end = 0; bol != 1 && section->value[end]; end++)
	{
		if (section->value[end] == ':' || section->value[end + 1] == '\0')
		{
			if (section->value[end + 1] == '\0')
				end++, bol = 1;
			exe = _calloc(len + (end - start) + 1, sizeof(char));
			_strncpy(exe, &section->value[start], end - start);
			_strcpy(&exe[end - start], file);
			if (access(exe, F_OK) == 0)
			{
				free(file);
				return (exe);
			}
			free(exe);
			start = end;
			start++;
		}
	}
	free(file);
	return (NULL);
}
