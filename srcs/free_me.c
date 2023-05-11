/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:58:23 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/11 23:10:50 by aessaoud         ###   ########.fr       */
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


void	free_redir_list(t_redir_list **redir_list_head)
{
	t_redir_list	*current;
	t_redir_list	*next;
	
	current = (*redir_list_head);
	while (current)
	{
		free(current->file_name);
		free(current->here_doc_text);
		next = current->next;
		free(current);
		current = next;
		(*redir_list_head) = NULL;
	}
}

void	free_cmd_data(t_cmd **cmd_node)
{
	free_arr((*cmd_node)->args);
	free_redir_list(&(*cmd_node)->redir_list);
}

void	free_tree(t_tree **tree)
{
	if ((*tree)->type == CMD_NODE)
	{
		free_cmd_data(&(*tree)->cmd_node);
		free((*tree)->cmd_node);
		free(*tree);
	}
	else
	{
		free_tree(&(*tree)->left);
		free_tree(&(*tree)->right);
		free(*tree);
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