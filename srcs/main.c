/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/05/10 19:36:12 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

char	*get_folder()
{
	char	s[100];
	int		i;
	int		l_i;
	char	*our_shell;

	getcwd(s, sizeof(s));
	i = -1;
	l_i = 0;
	while (s[++i])
	{
		if (s[i] == '/')
			l_i = i;
	}
	our_shell = ft_strjoin(ft_strdup("\e[1;32m("), ft_strdup(s + l_i));
	our_shell = ft_strjoin(our_shell, ft_strdup(")🍑~> \e[0;37m"));
	our_shell = ft_strjoin(ft_strdup("\e[0;31m/our@shell~:"), our_shell);
	return (our_shell);
}

int main(int c, char **arg, char **env)
{
	t_token	*tokens;
	char	*input;
	char	**new_env;
	t_tree	*tree;
	int		command_count;
	char	*our_shell;

	new_env = my_env(env);
	while(1)
	{
		our_shell = get_folder();
		input = readline(our_shell);
		free(our_shell);
		if(!input)
		{
			printf("khrj\n");
			exit(1);
		}
		if (!*input)
		{
			free(input);
			continue;
		}
		if(ft_strlen(input) > 0)
			add_history(input);
		input = ft_strtrim(input, " ");
		tokens = lets_tokenize(input);
		if (!check_tokens(tokens))
		{
			printf("Syntax Error !!\n");
			continue;
		}
		tree = lets_parse(&tokens);
		free_tokens(&tokens);
		// print_my_tree(tokens)
		// continue;
		lets_execute(tree, new_env, is_single_cmd(tree));
	}
	free_arr(new_env);
	return(0);
}
