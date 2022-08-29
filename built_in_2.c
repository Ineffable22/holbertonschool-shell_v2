#include "main.h"

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
 * print_working_directory - Prints the name of the current working directory
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *print_working_directory(general *go)
{
	char buff[1024];

	printf("%s\n", getcwd(buff, 1024));
	go->res = 0;
	go->bol = 1;
	return (go);
}

/**
 * exit_time - Exits the program with a status code
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *exit_time(general *go)
{
	int num = 0;

	if (go->token[1] == NULL)
	{
		free(go->buff);
		_free_env(go->env, go->PS1);
		_free_double(go->token);
		_free_tkn(go->tkn);
		free(go);
		exit(0);
	}
	if (go->token[2] != NULL)
	{
		go->msg = "too many arguments";
		message_error(go, 0, NULL);
		go->res = 1;
		go->bol = 1;
		return (go);
	}
	go->res = 0;
	num = _atoi(go->token[1], &go->res);
	if (go->res == 2)
	{
		go->msg = "numeric argument required";
		message_error(go, 0, NULL);
		go->bol = 1;
		return (go);
	}
	/*num = (num != 0) ? num : 2;*/
	free(go->buff);
	_free_env(go->env, go->PS1);
	_free_double(go->token);
	_free_tkn(go->tkn);
	free(go);
	exit(num);
}


/**
 * shell_setenv - Set a value in the Singly linked list Envi
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *shell_setenv(general *go)
{
	envi *env = NULL, *node = NULL, *tmp = go->env;

	if (go->token[1] && go->token[2])
	{
		if (!go->env)
			go->env = set_env(go->token[1], go->token[2], go->env);
		else
		{
			env = search_env(go->token[1], go->env);
			if (env == NULL)
			{
				node = _calloc(1, sizeof(envi));
				node->key = _calloc((_strlen(go->token[1]) + 1), sizeof(char));
				_strcpy(node->key, go->token[1]);

				node->value = _calloc((_strlen(go->token[2]) + 1), sizeof(char));
				_strcpy(node->value, go->token[2]);
				if (go->env == NULL)
					go->env = node;
				else
				{
					while (tmp->next)
						tmp = tmp->next;

					tmp->next = node;
				}
			}
			else
			{
				while (tmp->key != env->key)
					tmp = tmp->next;

				free(tmp->value);
				tmp->value = _calloc((_strlen(go->token[2]) + 1), sizeof(char));
				_strcpy(tmp->value, go->token[2]);
			}
		}
	}
	go->res = 0, go->bol = 1;
	return (go);
}

/**
 * shell_unsetenv - Unset a value in the Singly linked list Envi
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *shell_unsetenv(general *go)
{
	envi *env = NULL, *prev = NULL, *tmp = go->env;

	if (go->token[1])
	{
		env = search_env(go->token[1], go->env);
		if (env)
		{
			while (tmp->key != env->key)
			{
				prev = tmp;
				tmp = tmp->next;
			}
			if (prev == NULL)
				go->env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
	}
	go->res = 0;
	go->bol = 1;
	return (go);
}
