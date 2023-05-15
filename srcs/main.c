/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/05/15 22:03:01 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_valid_input(char *input)
{
	if(!input)
	{
		printf("khrj\n");
		exit(1);
	}
	if (is_empty(input))
		return (0);
	return (1);
}

void	tokenize_parse_execute(char *input, t_my_env **my_env, int *exit_code)
{
	t_token		*tokens;
	t_tree		*tree;

	if(ft_strlen(input) > 0)
			add_history(input);
	input = ft_strtrim(input, " ");
	tokens = lets_tokenize(input);
	print_tokens(tokens);
	return ;
	if (!check_tokens(tokens))
		return ;
	tree = lets_parse(&tokens);
	free_tokens(&tokens);
	lets_execute(tree, my_env, is_single_cmd(tree), exit_code);
	free_tree(&tree);
}

int main(int c, char **arg, char **env)
{
	char		*input;
	char		*our_shell;
	t_my_env	*my_env;
	static int	exit_code;

	my_env = NULL;
	copy_env(&my_env, env);
	while(1)
	{
		our_shell = get_cdir(exit_code);
		input = readline(our_shell);
		free(our_shell);
		if (!is_valid_input(input))
		{
			free(input);
			continue ;
		}
		tokenize_parse_execute(input, &my_env, &exit_code);
		free(input);
	}
	free_my_env(&my_env);
	return(0);
}
