


#include "test_header.h"


int	main(int c, char **args, char **env)
{
	t_my_env	*my_env;

	my_env = NULL;
	copy_env(&my_env, env);
	while (my_env)
	{
		printf("[%s]\n", my_env->val);
		my_env = my_env->next;
	}
	exit(0);
}