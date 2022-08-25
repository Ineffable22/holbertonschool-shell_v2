#include "main.h"

/**
 * _strcmp - Compares two strings
 * @s1: First string to compare
 * @s2: Second string to compare
 *
 * Return: Less than 0 if s1 is less than s2, 0 if they're equal,
 * more than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (!*s1 && !*s2)
		return (0);
	return (*s1 - *s2);
}

/**
 * _strlen - Counts the length of a string.
 * @s: string to evaluate
 * Return: The length of the string
 */

int _strlen(char *s)
{
	int i = 0;

	for (; s[i]; i++)
	{}
	return (i);
}

/**
 * _strlen2 - Counts the length of a double pointer.
 * @s: String to evaluate
 * Return: The length of the double pointer
 */
int _strlen2(char **s)
{
	int i = 0;

	for (i = 0; s[i]; i++)
	{}
	return (i);
}

/**
 * _strcpy - copies the string pointed to by src
 * including the terminating null byte (\0)
 * to the buffer pointed to by dest
 * @dest: Pointer to the buffer in which we copy the string
 * @src: String to be copied
 *
 * Return: Pointer to the resulting string
 */
char *_strcpy(char *dest, char *src)
{
	int n, i;

	n = 0;
	while (src[n] != 0)
	{
		n++;
	}
	for (i = 0; i < n; i++)
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}

/**
 * _strncpy - Copies a string up to n bytes
 * @dest: Destination string
 * @src: Source string
 * @n: Number of bytes to copy
 *
 * Return: Pointer to the resulting string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != 0; i++)
		dest[i] = src[i];
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
