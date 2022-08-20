#include "main.h"

void printer(envi *env)
{
	while(env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void _free(envi *env)
{
	if (env)
	{
		_free(env->next);
		free(env->key);
		free(env->value);
		free(env);
	}
}

void free_section(char **token, int res)
{
	while(token[res])
	{
		free(token[res]);
		res++;
	}
}