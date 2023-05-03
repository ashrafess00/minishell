/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/05/03 17:09:57 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	pipte[2];

int empty_command(char *input)
{
	int i = 0;
	int j = 0;
	while(input[i])
	{
		if(input[i] >= 65 && input[i] <= 90)
			j++;
		else if(input[i] >= 97 && input[i] <= 122)
			j++;
		i++;
	}
	if(j == 0)
		return(1);
	return(0);
}

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
int main(int c, char **arg, char **env)
{
	t_token	*tokens;
	char	*input;
	char **new_env = my_env(env);//hahwa char ** dyal lcopy d env
	t_tree	*tree;
	int *fds;
	int	pipe_count;

	while(1)
	{
		pipe_count = 0;
		input = readline("\e[0;31m/our@shell~:\e[0;37m ");
		if(!input)
		{
			printf("khrj");
			exit(1);
		}
		if (empty_command(input))
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
		tree = lets_parse(&tokens, &pipe_count);

		int count = 0;
		int fds_count = pipe_count * 2;
		int i = -1;
		fds = malloc(sizeof(int) * fds_count);
		while (++i < pipe_count)
			pipe(&fds[i * 2]);
		lets_execute(tree, new_env, fds, fds_count, &count);

		free(input);
	}
	return(0);
}

