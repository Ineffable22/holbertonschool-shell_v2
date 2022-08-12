#include "main.h"

general *go_match(general *go)
{
	int i = 0, res = 0;
	cmd flag_store[] = {
		{"env", print_env},
		{"whoami", who_am_i},
		{"clear", shell_clear},
		{"cd", change_directory},
		{"pwd", print_working_directory},
		{NULL, NULL}
	};

	for (i = 0; flag_store[i].c; i++)
	{
		res = strcmp(go->token[0], flag_store[i].c);
		if (res == 0)
		{
			go = flag_store[i].f(go);
			return (go);
		}
	}
	go->res = 0;
	return (go);
}
