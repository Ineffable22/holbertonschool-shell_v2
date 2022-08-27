#include "main.h"

/**
 * go_bypass - Create a bypass per command and its assigned routes for each
 * @go: Pointer to Structure General
 * @buffer: Buffer with command line
 *
 * Return: Pointer to Structure General
 */
general *go_bypass(general *go, char *buffer)
{
	go->buff = buffer;
	go->bol = 0, go->end = 0, go->fd = -1, go->fd1 = -1;
	go->field = NULL, go->tkn = NULL, go->token = NULL;
	go->std_in = -1, go->std_out = -1, go->operator = 0;
	add_history(go);
	while (add_token(&(go->tkn), strtok(buffer, " \t\n")) != NULL)
		buffer = NULL;
	if (go->tkn == NULL || *go->tkn->token == '#')
	{
		if (go->tkn)
			_free_tkn(go->tkn);
		return (go);
	}
	while (go->end == 0)
	{
		go->res = 0;
		go = validate_stream(go);
		if (go->res != 1 && go->res != 2)
		{
			go = built_in(go);
			if (go->bol == 0)
				go->bol = functions_bin(go);
			if (go->bol == 0)
			{
				go->msg = (go->res == 0) ? "command not found" : "not found";
				go->res = (go->res == 0) ? 127 : 2;
				message_error(go, 2, NULL);
			}
		}
		go->bol = 0;
		go = _free_fd(go);
		if (go->token)
			_free_double(go->token);
	}
	_free_tkn(go->tkn);
	return (go);
}

/**
 * validate_stream - Checks the stream type of the commands
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *validate_stream(general *go)
{
	tokens *finder = go->tkn;
	tokens *carry = NULL, *cmd = NULL;
	int total = 0, i = 0, res = 0;
	char *var = NULL;

	if (go->field)
		while (finder->token != go->field)
			finder = finder->next;
	carry = finder;
	while (finder)
	{
		total++;
		res = stream_match(go, finder, go->exe);
		if (res == FAILED_MSG || res == FAILED)
			return (go);
		if (res == SUCCESS)
			cmd = finder;
		if (res == FIELD)
			break;
		finder = finder->next;
	}
	if (res == FIELD)
	{
		if (cmd)
			go->field = cmd->next->token;
		else
		{
			go->field = finder->next->token, cmd = finder;
		}
	}
	if (res == SUCCESS || res == 10)
		go->end = 1;
	go->token = _calloc((total + 1), sizeof(char *));
	while (carry != cmd)
	{
		var = is_var(go->env, carry->token, go->res);
		go->token[i] = _calloc(_strlen(var) + 1, sizeof(char));
		_strcpy(go->token[i], var), carry = carry->next, i++;
	}
	return (go);
}

/**
 * is_var - Checks if buffer is a special command
 * @env: Pointer to Singly linked list with the environment variables
 * @buffer: String to compare
 * @res: Status code
 *
 * Return: String or special command
 */
char *is_var(envi *env, char *buffer, int res)
{
	char *num = NULL;
	envi *section = NULL;

	if (buffer[0] == '$' && buffer[1])
	{
		if (buffer[1] == '?')
		{
			num = itoa(res, 10);
			if (_strlen(num) == 0)
				num = "0";
			return (num);
		}
		else if (buffer[1] == '$')
		{
			num = itoa(getpid(), 10);
			return (num);
		}
		section = search_env(&buffer[1], env);
		if (section != NULL)
			return (section->value);
	}
	return (buffer);

}

/**
 * add_token - Saves the token in the singly linked list Token
 * @token: Pointer to Singly linked list with the tokens
 * @buffer: Value to insert in the node
 *
 * Return: Singly linked list with the tokens
 */
tokens *add_token(tokens **token, char *buffer)
{
	tokens *node = NULL, *tmp = (*token);

	if (buffer == NULL)
		return (NULL);
	node = _calloc(1, sizeof(tokens));

	node->token = _calloc(_strlen(buffer) + 1, sizeof(char));
	if (node->token == NULL)
	{
		fprintf(stderr, "Can't malloc\n");
		return (NULL);
	}
	_strcpy(node->token, buffer);
	node->next = NULL;

	if ((*token) == NULL)
	{
		(*token) = node;
		return (node);
	}

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (node);
}

/**
 * add_history - Saves the commands in the history
 * @go: Pointer to Structure General
 *
 * Return: Nothing
 */
void add_history(general *go)
{
	int fd = 0;
	envi *section = NULL;
	char *file = NULL;
	char *name = "/.hsh_history";

	if (!go->env)
		return;
	section = search_env("HOME", go->env);
	if (section == NULL)
		return;

	file = malloc((_strlen(name) + _strlen(section->value) + 1) * sizeof(char));
	_strcpy(file, section->value);
	_strcpy(&file[_strlen(section->value)], name);

	fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd == -1)
		exit(-1);
	free(file);
	write(fd, go->buff, _strlen(go->buff));
	if (go->is_file == 1)
		write(fd, "\n", 1);
	close(fd);
}
