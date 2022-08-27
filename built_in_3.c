#include "main.h"

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
