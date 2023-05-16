/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:27:41 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/16 17:57:36 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*cr_token_node(char *s, t_special_char type)
{
	t_token *new_token_node;

	new_token_node = malloc(sizeof(t_token));
	new_token_node->s = ft_strdup(s);
	free(s);
	new_token_node->s = remove_quotes(new_token_node->s);
	new_token_node->type = type;
	new_token_node->next = NULL;
	return (new_token_node);
}

void	add_token(t_token **head, char *s, t_special_char type)
{
	t_token	*new_token_node;
	t_token	*last;

	if (ft_strlen(s) == 0)
	{
		free(s);
		return ;
	}
	last = *head;
	new_token_node = cr_token_node(s, type);
	if (*head == NULL)
	{
		// new_token_node->prev = NULL;
		*head = new_token_node;
	}
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_token_node;
		// new_token_node->prev = last;
	}
}
