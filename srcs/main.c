/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/05/15 15:35:23 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	exit_code = 0;

int	check_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->s)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

int	is_single_cmd(t_tree *tree)
{
	if (tree->type == PIPE_NODE)
		return (0);
	else
		return (1);
}

int	is_empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] != ' ' && input[i] != '\n'
				&& input[i] != '\t' && input[i] != '\f' 
				&& input[i] != '\v' && input[i] != '\r')
			return (0);
	}
	return(1);
}

int main(int c, char **arg, char **env)
{
	t_token		*tokens;
	t_tree		*tree;
	char		*input;
	char		*our_shell;
	t_my_env	*my_env;
	

	my_env = NULL;
	copy_env(&my_env, env);
	while(1)
	{
		our_shell = get_cdir(exit_code);
		input = readline(our_shell);
		free(our_shell);
		if(!input)
		{
			printf("khrj\n");
			exit(1);
			// continue;
		}
		if (is_empty(input))
		{
			free(input);
			continue;
		}
		if(ft_strlen(input) > 0)
			add_history(input);
		input = ft_strtrim(input, " ");
		tokens = lets_tokenize(input);
		enter_a_pipe(&tokens);
		if (!check_tokens(tokens))
		{
			printf("Syntax Error !!\n");
			continue;
		}
		tree = lets_parse(&tokens);
		free_tokens(&tokens);
		lets_execute(tree, &my_env, is_single_cmd(tree), &exit_code);
		free_tree(&tree);
	}
	free_my_env(&my_env);
	return(0);
}
