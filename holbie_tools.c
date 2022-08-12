#include "main.h"

int _strstr(char *s1, char *s2)
{
	while(*s1 == *s2 && *s1 != '=')
	{
		if (*s1 == 0)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 == '=')
		return (1);
	return (0);
}

int _strncmp(char *s1, char *s2, int n)
{
	while(*s1 == *s2 && n != 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0 && *s2 == 0)
		return (1);
	return (0);
}


/**
 * _strlen - returns the length of a string.
 * @s: string to evaluate
 * Return: the length of the string
 */

int _strlen(char *s)
{
	int i = 0;

	for (;s[i]; i++)
	{}
	return (i);
}

/**
 * _strlen2 - returns the length of a double pointer.
 * @s: string to evaluate
 * Return: the length of the string
 */
int _strlen2(char **s)
{
	int i = 0;

	for (i = 0; s[i]; i++)
	{}
	return (i);
}
/**
 * *_strcpy - copies the string pointed to by src
 * including the terminating null byte (\0)
 * to the buffer pointed to by dest
 * @dest: pointer to the buffer in which we copy the string
 * @src: string to be copied
 *
 * Return: the pointer to dest
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
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to copy
 *
 * Return: pointer to the resulting string
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

/**
 * *_calloc - allocates memory for an array
 * @nmemb: number of elements in the array
 * @size: size of each element
 *
 * Return: pointer to allocated memory
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *p;
	unsigned int i;

	if (nmemb == 0 || size == 0)
		return (NULL);

	p = malloc(nmemb * size);

	if (p == NULL)
		return (NULL);

	for (i = 0; i < (nmemb * size); i++)
		*(p + i) = 0;
	return (p);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previsouly allocated by malloc
 * @size: size or new size of the new memory block
 *
 * Return: pointer to the newly allocated memory block
 */
char *_realloc(char *ptr, unsigned int size)
{
	char *ptr1 = NULL;

	if (size == 0)
		return (NULL);
	if (ptr == NULL)
	{
		ptr = malloc(size);
		if (ptr == NULL)
			return (NULL);
		memset(ptr, 0, size);
		return (ptr);
	}
	ptr1 = malloc(size);
	if (ptr1 == NULL)
		return (NULL);
	memset(ptr1, 0, size);
	ptr1 = _strcpy(ptr1, ptr);
	free(ptr);
	return (ptr1);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: less than 0 if s1 is less than s2, 0 if they're equal,
 * more than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == 0)
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
