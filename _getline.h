#ifndef _GETLINE_H
#define _GETLINE_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_SIZE 4096

/**
 * struct Superbuffer - Struct that stores all the flags in the stream.
 * This structure was invoked as static.
 * @buff: Is a pointer that stores everything read by position.
 * @data: Is a pointer with flags to create_stream function
 * @next: Pointer to the next node in the struct Superbuffer
 */
typedef struct Superbuffer
{
	char buff[READ_SIZE];
	int data[4];
	struct Superbuffer *next;
} supabuffa;

char *_getline(const int fd);

#endif
