/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/04/21 21:30:47 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


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
int main()
{
	t_token	*tokens;
	
	char	*input;
	while(1)
	{
		//hadi 7ttitha hna 3la 7sab l color wsafi
		printf("\e[0;31m/our@shell~: ");
		input = readline("\e[0;37m");
		if(!input)
		{
			printf("khrj");
			exit(1);
		}
		if(strlength(input) > 0)
			add_history(input);
		input = ft_strtrim(input, " ");
		tokens = lets_tokenize(input);
		print_tokens(tokens);
		// lets_parse(&tokens);
	}
	return(0);
}