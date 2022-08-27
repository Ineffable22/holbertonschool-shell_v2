#include "main.h"

/**
 * PS1 - Changes the prompt
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *PS1(general *go)
{
	if (go->token[1] == NULL)
		printf("Insert an argument\n");
	else
	{
		if (go->PS1)
			free(go->PS1);
		go->PS1 = malloc((_strlen(go->token[1]) + 1) * sizeof(char));
		if (go->PS1 == NULL)
		{
			fprintf(stderr, "Can't malloc\n");
			exit(-1);
		}
		_strcpy(go->PS1, go->token[1]);
	}
	go->res = 0;
	go->bol = 1;
	return (go);

}

/**
 * alias - In process
 * @go: Pointer to Structure General
 *
 * Return: Pointer to Structure General
 */
general *alias(general *go)
{
	printf("alias\n");
	go->res = 0;
	go->bol = 1;
	return (go);
}
