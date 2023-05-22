/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_me2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:39:56 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/22 13:43:22 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

void	free_pedi(char *pedi)
{
	int	i;

	i = 0;
	while (pedi[i] != '\0')
	{
		pedi[i] = '\0';
		i++;
	}
}

void	freenode(t_my_env *node)
{
	free(node->val);
	free(node);
}
