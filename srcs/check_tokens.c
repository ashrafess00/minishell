/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:47:49 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/12 18:07:59 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_pipe(char *s, char q, int *error)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (s[0] == '|')
	{
		count += 1;
		while (s[++i])
		{
			if (s[i] == '|')
				count ++;
			if (count == 2 && q == 'c')
			{
				printf("syntax error : unexpected token %c\n", s[i]);
				*error = 1;
				return (0);
			}
			if (s[i] != ' ')
				return (1);
		}
	}
	return (0);
}

int is_heredoc(char *s, char q, int *error)
{
	int count;
	int i;

	i = 1;
	
	if (s[0] == '<' && s[1] == '<')
	{
		count = 2;
		while (s[++i])
		{
			if (s[i] == '<' || s[i] == '>' || s[i] == '|')
				count++;
			if (count > 2)
			{
				printf("syntax error : unexpected token [d%c\n", s[i]);
				
				*error = 1;
				return (0);
			}
			if (s[i] != ' ')
				return (1);
		}
	}
	return (0);
}

int	is_red_input_append(char *s, char q, int *error)
{
	int count;
	int i;

	i = 1;
	
	if (s[0] == '>' && s[1] == '>')
	{
		count = 2;
		while (s[++i])
		{
			if (s[i] == '<' || s[i] == '>' || s[i] == '|')
				count++;
			if (count > 2)
			{
				printf("syntax error : unexpected token %c\n", s[i]);
				*error = 1;
				return (0);
			}
			if (s[i] != ' ')
				return (1);
		}
	}
	return (0);
}

int is_red_output(char *s, char q, int *error)
{
	int	count;
	int	i;

	i = -1;
	if (s[0] == '>' && s[1] == '|')
	{
		*error = 1;
		printf("syntax error : unexpected token %c\n", s[i]);
		return (0);
	}
	else if (s[0] == '>')
		return (1);
	return (0);
}

int is_red_input(char *s, char q, int *error)
{
	int	count;
	int	i;

	i = -1;
	if (s[0] == '<' && s[1] == '|')
	{
		*error = 1;
		printf("syntax error : unexpected token %c\n", s[i]);
		return (0);
	}
	else if (s[0] == '<')
		return (1);
	return (0);
}