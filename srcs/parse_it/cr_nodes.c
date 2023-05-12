/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:22:20 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/12 12:38:18 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_tree	*cr_tree()
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}
	tree->cmd_node = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_cmd	*cr_cmd()
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}
	// new_cmd->args = ft_calloc(100, sizeof(char *));
	new_cmd->args = NULL;
	new_cmd->redir_list = NULL;
	return (new_cmd);
}

//create node of the redirection with opening files and getting heredoc_data
t_redir_list	*cr_redir_list_node(char *file_name, t_special_char type)
{
	t_redir_list	*new_redir_list;

	new_redir_list = malloc(sizeof(t_redir_list));
	if (!new_redir_list)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}
	new_redir_list->here_doc_text = NULL;
	if (type == HEREDOC)
		new_redir_list->here_doc_text = get_input_from_usr(file_name);
	new_redir_list->file_name = ft_strdup(file_name);
	new_redir_list->type = type;
	new_redir_list->next = NULL;
	return (new_redir_list);
}

void	add_redir_list_node(t_redir_list **head, char *file_name, t_special_char type)
{
	t_redir_list	*temp;

	if (!(*head))
		(*head) = cr_redir_list_node(file_name, type);
	else
	{
		temp = (*head);
		while (temp->next)
			temp = temp->next;
		temp->next = cr_redir_list_node(file_name, type);
		
	}
}

t_cmd	*cr_cmd_node(t_token **tokens)
{
	t_cmd	*cmd;
	int		i;

	cmd = cr_cmd();
	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == RED_OUTPUT)
		{
			*tokens = (*tokens)->next;
			add_redir_list_node(&cmd->redir_list, (*tokens)->s, RED_OUTPUT);
		}
		else if ((*tokens)->type == RED_INPUT)
		{
			*tokens = (*tokens)->next;
			add_redir_list_node(&cmd->redir_list, (*tokens)->s, RED_INPUT);
		}
		else if ((*tokens)->type == RED_OUTPUT_APPEND)
		{
			*tokens = (*tokens)->next;
			add_redir_list_node(&cmd->redir_list, (*tokens)->s, RED_OUTPUT_APPEND);
		}
		else if ((*tokens)->type == HEREDOC)
		{
			*tokens = (*tokens)->next;
			add_redir_list_node(&cmd->redir_list, (*tokens)->s, HEREDOC);
		}
		else
		{
			cmd->args = expand_arr(cmd->args, (*tokens)->s);
			i++;
		}
		*tokens = (*tokens)->next;
	}
	return (cmd);
}