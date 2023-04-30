/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/04/30 11:58:17 by aessaoud         ###   ########.fr       */
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

//finished prompt + check empty command + working history
int main(int c, char **arg, char **env)
{
	t_token	*tokens;
	char	*input;
	char **new_env = my_env(env);//hahwa char ** dyal lcopy d env
	t_tree	*tree;
	while(1)
	{
		input = readline("\e[0;31m/our@shell~:\e[0;37m ");
		if(!input)
		{
			printf("khrj");
			exit(1);
		}
		if(strlength(input) > 0)
			add_history(input);
		input = ft_strtrim(input, " ");
		tokens = lets_tokenize(input);
		// print_tokens(tokens);
		tree = lets_parse(&tokens);
		lets_execute(tree, new_env);
		free(input);
	}
	return(0);
}

