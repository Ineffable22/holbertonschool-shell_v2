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
/*
void _free2(char **env)
{
	while (go->env)
	{
		free(go->env->key);
		free(go->env->value);
		free(go->env);
		go->env = go->env->next;
	}
}*/