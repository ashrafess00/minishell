/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/05/20 11:31:42 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_valid_input(char *input)
{
	if (!input)
		exit(1);
	if (is_empty(input))
		return (0);
	return (1);
}

void	tokenize_parse_execute(char *input, t_my_env **my_env, int *exit_code)
{
	t_token		*tokens;
	t_tree		*tree;

	if (ft_strlen(input) > 0)
		add_history(input);
	input = ft_strtrim(input, " ");
	tokens = lets_tokenize(input);
	free(input);
	if (!check_tokens(tokens))
		return ;
	tree = lets_parse(&tokens);
	free_tokens(&tokens);
	lets_execute(tree, my_env, is_single_cmd(tree), exit_code);
	printf("exit code : %d\n", *exit_code);
	free_tree(&tree);
}
void ctrl_c_handler(int signum) 
{
	if(signum == SIGINT)
	{
    	rl_on_new_line();
    	// rl_replace_line("", 0);
    	// write(1,"\n",1);
    	rl_redisplay();
	} 
}
#include <stdlib.h>
#include <string.h>

void free_pedi(char *pedi)
{
	int i = 0;
	while(pedi[i] != '\0')
	{
		pedi[i] = '\0';
		i++;
	}
}
char *expand_quote(char *input)
{
	int i = 0;
	int j = 0;
	char *retr = malloc(ft_strlen(input) + 2);
	while(input[i] != '\0')
	{
		if(input[i] == 34)
			i++;
		else
		{
			retr[j] = input[i];
			i++;
			j++;
		}
	}
	retr[j] = '\0';
	return (retr);
}
char *expandini(char *input, t_my_env *my_env)
{
    char *result = malloc(strlen(input) * 3 + 1);
    int resultIndex = 0;
	char pedi[200];
	int position = 0;
	int i = 0;
	t_my_env	*tmp;
	int c = 0;
	int fl =0;
    int inputIndex = 0;
	input = expand_quote(input);
    while (input[inputIndex] != '\0')
    {
		position = 0;
		fl = 0;
		if(inputIndex > 0)
		{
			if(input[inputIndex - 1] == 39)
				fl = 1;
		}
        if (input[inputIndex] == '$' && fl == 0)
        {
			c = 0;
			inputIndex++;
            while(input[inputIndex] != ' ' && input[inputIndex])
			{
				pedi[c] = input[inputIndex];
				inputIndex++;
				c++;
			}
			pedi[c] = '\0';
			tmp = my_env;
			while(tmp != NULL)
			{
				i = 0;
				while(tmp->val[i] != '\0' && pedi[i] != '\0' && tmp->val[i] == pedi[i])
					i++;
				if(pedi[i] == '\0')
				{
					i = 0;
					while(tmp->val[i] != '=' && tmp->val[i])
						i++;
					i++;
					while(tmp->val[i] != '\0')
					{
						result[resultIndex] = tmp->val[i];
						i++;
						resultIndex++;
					}
				}
				tmp = tmp->next;
			}
			free_pedi(pedi);
        }
		if(input[inputIndex] != '\0')
		{
        	result[resultIndex] = input[inputIndex];
        	resultIndex++;
        	inputIndex++;
		}
    }
    result[resultIndex] = '\0';
    return result;
}

int	main(int c, char **arg, char **env)
{
	char		*input;
	char		*our_shell;
	t_my_env	*my_env;
	static int	exit_code;

	my_env = NULL;
	copy_env(&my_env, env);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		our_shell = get_cdir(exit_code);
		input = readline(our_shell);
		// free(our_shell);
		if (!is_valid_input(input))
		{
			free(input);
			continue ;
		}
		input = expandini(input, my_env);
		printf("%s\n", input);
		tokenize_parse_execute(input, &my_env, &exit_code);
	}
	free_my_env(&my_env);
	return (0);
}
