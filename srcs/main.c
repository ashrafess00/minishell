/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/05/09 13:24:15 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int strlength(char *input)
{
	int i = 0;
	while(input[i] != '\0')
		i++;
	return (i);
}

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
	char	*last_folder;

	getcwd(s, sizeof(s));
	i = -1;
	l_i = 0;
	while (s[++i])
	{
		if (s[i] == '/')
			l_i = i;
	}
	last_folder = ft_strjoin(ft_strdup("\e[1;32m("), ft_strdup(s + l_i));
	last_folder = ft_strjoin(last_folder, ft_strdup(")🍑~> \e[0;37m"));
	return (last_folder);
}

int main(int c, char **arg, char **env)
{
	t_token	*tokens;
	char	*input;
	char	**new_env;
	t_tree	*tree;
	int		command_count;
	char	*last_folder ;

	new_env = my_env(env);
	while(1)
	{
		last_folder = get_folder();
		printf("\e[0;31m/our@shell~:");
		input = readline(last_folder);
		free(last_folder);
		if(!input)
		{
			printf("khrj\n");
			exit(1);
		}
		if (!*input)
			continue;
		if(strlength(input) > 0)
			add_history(input);
		input = ft_strtrim(input, " ");
		tokens = lets_tokenize(input);
		free(input);
		// print_tokens(tokens);
		// continue;
		if (!check_tokens(tokens))
		{
			printf("Syntax Error !!\n");
			continue;
		}
		tree = lets_parse(&tokens);
		// print_my_tree(tree);
		// continue;
		lets_execute(tree, env, is_single_cmd(tree));
	}
	return(0);
}

