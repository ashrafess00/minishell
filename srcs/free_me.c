/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:58:23 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/15 20:40:28 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_tokens(t_token **tokens_head)
{
	t_token	*current;
	t_token	*next;

	current = (*tokens_head);
	while (current)
	{
		free(current->s);
		next = current->next;
		free(current);
		current = next;
		(*tokens_head) = NULL;
	}
}

void	free_my_env(t_my_env **my_env_head)
{
	t_my_env	*current;
	t_my_env	*next;

	current = (*my_env_head);
	while (current)
	{
		free(current->val);
		next = current->next;
		free(current);
		current = next;
		(*my_env_head) = NULL;
	}
}
