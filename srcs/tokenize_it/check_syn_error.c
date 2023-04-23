/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syn_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:51:12 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/23 15:11:59 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
int strln(char *line)
{
	int i = 0;
	while(line[i])
		i++;
	return(i);
}

char *dble(char *line, int i)
{ 
	int j = strln(line) - 1;
	i = i + 1;
	while(j > 0)
	{
		if (line[j] == '*')
			break;
		j--;
	}
	if(i >= j)
		line[i - 1] = '*';
	else
		return line;
	while(line[i])
	{
		if(line[i] == '"' && i >= j)
		{
			line[i] = '*';
			return(line);
		}
		i++;
	}
	return NULL;
}
char *sngle(char *line, int i)
{
	int j = strln(line) - 1;
	i = i + 1;
	while(j > 0)
	{
		if (line[j] == '*')
			break;
		j--;
	}
	if(i >= j)
		line[i - 1] = '*';
	else
		return line;
	while(line[i])
	{
		if(line[i] == 39 && i >= j)
		{
			line[i] = '*';
			return(line);
		}
		i++;
	}
	return(NULL);
}
char *no_star(char *line)
{
	char *line2;
	int j = 0;
	line2 = malloc(strln(line) * sizeof (char *) + 1);
	int i = 0;
	while(line[j] != '\0')
	{
		while(line[j] == '*')
			j++;
		line2[i] = line[j];
		i++;
		j++;
	}
	line2[i] = '\0';
	return(line2);
}

char *closeDOUBLE_QUOTE(char *line)
{
	char *line2;
	int i = 0;
	line2 =  malloc(strln(line) * sizeof(char *));
	while(line[i] != '\0')
	{
		line2[i] = line[i];
		i++;
	}
	line2[i] = '\0';
	i = 0;
	while(line2[i] != '\0')
	{
		if(line2[i] == '"')
			line2 = dble(line2, i);
		if(line2 == NULL)
			return NULL;
		if(line2[i] == 39)
			line2 = sngle(line2, i);
		i++;
	}
	line2 = no_star(line2);
	return (line2);
}