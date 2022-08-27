#include "main.h"

/**
 * _strncmp - Compares two strings up to n bytes
 * @s1: First string to compare
 * @s2: Second string to compare
 * @n: Number of bytes to compare
 *
 * Return: 1 if they're equal or 0 otherwise
 */
int _strncmp(char *s1, char *s2, int n)
{
	while (*s1 == *s2 && n != 0)
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
 * _calloc - Allocates memory for an array
 * @nmemb: Number of elements in the array
 * @size: Size of each element
 *
 * Return: Pointer to allocated memory
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
 * _realloc - Reallocates a memory block using malloc and free
 * @ptr: Pointer to the memory previsouly allocated by malloc
 * @size: Size or new size of the new memory block
 *
 * Return: Pointer to the newly allocated memory block
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
 * _lexers_cmp - Compares two strings
 * @s1: First string to compare
 * @s2: Second string to compare
 * @i: Ubication of pointer function
 *
 * Return: 1 if they are equal, -1 if it fails, and n if it has FD
 */
int _lexers_cmp(char *s1, char *s2, int i)
{
	int n = 0;

	if (_strcmp(s1, s2) == 0)
		return (1);
	if (i == 0)
	{
		n = *s1 - 48;
		if (n >= 0 && n <= 9)
		{
			s1++;
			if (_strcmp(s1, s2) == 0)
				return (n);
		}
	}
	return (-1);
}

/**
 * itoa - Converts a number to a string
 * @val: Number to convert
 * @base: Number base
 *
 * Return: String with number
 */
char *itoa(int val, int base)
{
	static char buf[32] = {0};
	int i = 30;

	for (; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];

	return (&buf[i + 1]);
}
