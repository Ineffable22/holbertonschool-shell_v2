#include "main.h"

/**
 * printer - Prints the environment variables
 * @env: Pointer to Singly linked list with the environment variables
 *
 * Return: Nothing
 */
void printer(envi *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

/**
 * _free_env - Free the environment variables of the Singly linked Envi
 * @env: Pointer to Singly linked list with the environment variables
 * @PS1: Custom prompt
 *
 * Return: Nothing
 */
void _free_env(envi *env, char *PS1)
{
	if (env)
	{
		_free_env(env->next, PS1);
		free(env->key);
		free(env->value);
		free(env);
	}
	else
	{
		if (PS1)
			free(PS1);
	}
}

/**
 * _free_tkn - Free the tokens of the Singly linked list Tokens
 * @tkn: Pointer to Singly linked list Tokens
 *
 * Return: Nothing
 */
void _free_tkn(tokens *tkn)
{
	if (tkn)
	{
		_free_tkn(tkn->next);
		free(tkn->token);
		free(tkn);
	}
}

/**
 * _free_double - Free a double pointer of chars
 * @token: Double pointer to free
 *
 * Return: Nothing
 */
void _free_double(char **token)
{
	int i = 0;

	while (token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
}

/**
 * message_error - Prints a error message
 * @go: Pointer to Structure General
 * @val: Value to evaluate
 * @tok: String to print
 *
 * Return: Nothing
 */
void message_error(general *go, char val, char *tok)
{
	if (val == 0)
	{
		if (isatty(STDIN_FILENO))
		{
			if (go->token[1] && tok)
				printf("%s: %s: %s: %s\n", go->exe, go->token[0], go->msg, go->token[1]);
			else
				printf("%s: %s: %s\n", go->exe, go->token[0], go->msg);
		}
		else
		{
			if (go->token[1] && tok)
				printf("%s: %d: %s: %s: %s\n", go->exe, go->n,
				go->token[0], go->token[1], go->msg);
			else
				printf("%s: %d: %s: %s\n", go->exe, go->n,
				go->token[0], go->msg);
		}
	}
	else if (val == 1)
	{
		go->msg = "No such file or directory";
		if (isatty(STDIN_FILENO))
			printf("%s: %s: %s\n", go->exe, tok, go->msg);
		else
			printf("%s: %d: %s: %s\n", go->exe, go->n, tok, go->msg);
	}
	else if (val == 2)
	{
		if (isatty(STDIN_FILENO) && go->env)
			printf("%s: %s\n", go->token[0], go->msg);
		else
		{
			if (go->res == 2)
				printf("%s: %d: '%s %s %s'\n", go->exe, go->n,
				go->token[0], go->token[1], go->token[2]);
			else
				printf("%s: %d: %s: %s\n", go->exe, go->n, go->token[0], go->msg);
		}
	}
}
