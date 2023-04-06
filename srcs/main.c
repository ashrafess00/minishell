/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:09 by kslik             #+#    #+#             */
/*   Updated: 2023/04/06 20:45:01 by aessaoud         ###   ########.fr       */
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
	char *input;
	while(1)
	{
		input = readline("/our@shell~: ");
		if(!input)
		{
			printf("khrj");
			exit(1);
		}
		if(empty_command(input))
			return(1);
		if(strlength(input) > 0)
			add_history(input);
		
	}
	return(0);
}