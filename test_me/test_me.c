
#include "test_header.h"

char *expandini(char *input, t_my_env	*my_env)
{
	t_my_env	*tmp;
	int i =0;
	int c = 0;
	int remeber;
	char *reurn;
	char tompe[200];
	int k = 0;
	int khrj = 0;
	tmp = my_env;
	while(input[i])
	{
		if(input[i] == '$')
		{
			remeber = i;
			i++;
			while(((input[i] >= 97 && input[i] <= 122) || (input[i] >= 65 && input[i] <= 90)) && input[i])
			{
				tompe[c] = input[i];
				c++;
				i++;
			}
			break;
		}
	}
	while(tmp != NULL)
	{
		i = 0;
		khrj = 0;
		while(tmp->val[i] != '=' && tmp->val[i])
		{
			if(tmp->val[i] == tompe[i])
			{
				while(tompe[i] != '\0')
				{
					if(tmp->val[i] != tompe[i])
					{
						khrj = 1;
						break;
					}
					i++;
				}
				
			}
			i++;
		}
		if(khrj == 1)
		{
			reurn = malloc(ft_strlen(input + i + 2));
			i = 0;
			k = 0;
			c= 0;
			while(i <= remeber)
			{
				reurn[k] = input[i];
				k++;
				i++;
			}
			while(input[i] != '$' && input[i])
				i++;
			while((input[i] >= 97 && input[i] <= 122) || (input[i] >= 65 && input[i] <= 90))
				i++;
			while(tmp->val[c] != '=')
				c++;
			while(tmp->val[c] != '\0')
			{
				reurn[k] = tmp->val[c];
				c++;
				k++;
			}
			while(input[i])
			{
				reurn[k] = input[i];
				k++;
				c++;
			}
			reurn[k] = '\0';
		}
		tmp = tmp->next;
	}
	return(reurn);
}

int	main(int c, char **args, char **env)
{
	char *s;
	expandini(args[1], env);
}