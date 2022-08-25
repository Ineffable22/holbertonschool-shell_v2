#include "_getline.h"

/**
 * _realloc2 - Reallocates a memory block using malloc and free
 * @ptr: Pointer to the memory previsouly allocated by malloc
 * @size: Size or new size of the new memory block
 *
 * Return: Pointer to the newly allocated memory block
 */
void *_realloc2(void *ptr, unsigned int size)
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
	ptr1 = memcpy(ptr1, ptr, size - 2);
	free(ptr);
	return (ptr1);
}

/**
 * _free - Free a pointer to structure
 * @sb: Is a pointer to structure that stores all the flags in the stream.
 *
 * Return: Nothing.
 */
supabuffa *_free(supabuffa *sb)
{
	if (sb)
	{
		_free(sb->next);
		free(sb);
		sb = NULL;
	}
	return (sb);
}

/**
 * create_stream - Create a getline stream per fp
 * @sb: Is a pointer to structure that stores all the flags in the stream.
 * @line: Is a pointer to the line read from the buffer.
 * @fd: Is the file descriptor to read
 * @rd: Variable that informs if the reading fails
 *
 * Return: Line with dynamic memory.
 */
supabuffa *create_stream(supabuffa *sb, char **line, int fd, int *rd)
{
	int new_line = 0;
	supabuffa *tmp = sb;

	while (tmp->data[3] != fd)
		tmp = tmp->next;
	while (1)
	{
		if (tmp->data[1] == 0)
		{
			*rd = read(tmp->data[3], tmp->buff, READ_SIZE);
			if (*rd == -1)
				return (sb);
			if (*rd == 0)
				break;
		}
		for (; tmp->data[0] < READ_SIZE; tmp->data[0]++)
		{
			if (tmp->buff[tmp->data[0]] == '\n')
			{
				new_line = 1, tmp->data[0] += 1;
				break;
			}
		}
		*line = _realloc2(*line,
		((tmp->data[0] + tmp->data[2] - tmp->data[1]) * sizeof(char))  + 1);
		memcpy(&(*line)[tmp->data[2]], &tmp->buff[tmp->data[1]],
		tmp->data[0] - new_line - tmp->data[1]);
		tmp->data[2] += tmp->data[0] - tmp->data[1];
		if (tmp->data[0] == READ_SIZE && tmp->buff[tmp->data[0] - 1] != '\n')
		{
			memset(tmp->buff, 0, READ_SIZE);
			tmp->data[0] = 0, tmp->data[1] = 0;
			continue;
		}
		if (!(new_line == 1 && tmp->data[0] != READ_SIZE && tmp->buff[tmp->data[0]]))
			tmp->data[0] = 0;
		tmp->data[1] = tmp->data[0], tmp->data[2] = 0;
		break;
	}
	return (sb);
}

/**
 * validate - Validate if the same fd exists in sb
 * @sb: Is a pointer to structure that stores all the flags in the stream.
 * @fd: Is the file descriptor to read
 *
 * Return: A position of fd in sb.
 */
int validate(supabuffa **sb, int fd)
{
	supabuffa *tmp = NULL, *prev = NULL, *node = NULL;

	tmp = *sb;
	while (tmp)
	{
		if (tmp->data[3] == fd)
			return (0);
		prev = tmp;
		tmp = tmp->next;
	}
	node = _realloc2(node, sizeof(supabuffa));
	if (node == NULL)
		return (fd);
	node->data[3] = fd;
	node->next = NULL;
	prev->next = node;
	return (0);
}

/**
 * _getline - Reads an entire line from a file descriptor
 * @fd: Is the file descriptor to read
 *
 * Return: If there are no more lines to return, or if there is an error,
 * the function should return NULL
 */
char *_getline(const int fd)
{
	static supabuffa *sb;
	char *line = NULL;
	int rd = 0;

	if (READ_SIZE <= 0)
		return (NULL);
	if (fd != -1)
	{
		if (!sb)
		{
			sb = _realloc2(sb, sizeof(supabuffa));
			if (sb == NULL)
				return (NULL);
			sb->data[3] = fd;
		}
		else
			rd = validate(&sb, fd);
		if (rd == 0)
			sb = create_stream(sb, &line, fd, &rd);
		if (rd == -1)
		{
			sb = _free(sb);
			return (line);
		}
	}
	if (fd == -1)
		sb = _free(sb);
	return (line);
}
