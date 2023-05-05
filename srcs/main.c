/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/05/05 21:18:30 by aessaoud         ###   ########.fr       */
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
	if (tree->type == PIPE)
		return (0);
	else
		return (1);
}

char	*get_folder()
{
	char	s[100];
	int		i;
	int		l_i;

	getcwd(s, sizeof(s));
	i = -1;
	l_i = 0;
	while (s[++i])
	{
		if (s[i] == '/')
			l_i = i;
	}
	char *last_folder;

	last_folder = ft_strjoin(ft_strdup("\e[1;32m("), ft_strdup(s + l_i));
	last_folder = ft_strjoin(last_folder, ft_strdup(")~> \e[0;37m"));
	return (last_folder);
}
int main(int c, char **arg, char **env)
{
	t_token	*tokens;
	char	*input;
	char **new_env;
	t_tree	*tree;
	int		command_count;
	char	*last_folder;

	last_folder = get_folder();
	while(1)
	{
		new_env = my_env(env);
		printf("\e[0;31m/our@shell~:");
		input = readline(last_folder);
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
		if (!check_tokens(tokens))
		{
			printf("Syntax Error !!\n");
			continue;
		}
		tree = lets_parse(&tokens);
		lets_execute(tree, env, is_single_cmd(tree));
		free(input);
	}
	return(0);
}

