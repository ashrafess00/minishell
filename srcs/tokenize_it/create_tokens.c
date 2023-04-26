/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:27:41 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/26 21:09:41 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*cr_token_node(char *s, int s_index, int size, t_special_char type)
{
	t_token *new_token_node;

	new_token_node = malloc(sizeof(t_token));
	new_token_node->s_index = s_index;
	//---------------------------------------------------------------------------------------
	new_token_node->s = ft_substr(s + s_index, 0, size);
	//fl function dyalk siftliha (ft_substr(s + s_index, 0, size)), substr ghadi tjiblik string kif mma hwwa like ("ec"h"o"), new_dl->s khas ydkhl fiha (echo)
	//---------------------------------------------------------------------------------------
	new_token_node->size = size;
	new_token_node->type = type;
	new_token_node->next = NULL;
	return (new_token_node);
}

void	add_token(t_token **head, char *s, int s_index, int size, t_special_char type)
{
	t_token	*new_token_node;
	t_token	*last;

	if (size == 0)
		return ;
	last = *head;
	new_token_node = cr_token_node(s, s_index, size, type);
	if (*head == NULL)
	{
		new_token_node->prev = NULL;
		*head = new_token_node;
	}
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_token_node;
		new_token_node->prev = last;
	}
}