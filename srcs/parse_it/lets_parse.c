/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:47:55 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/16 13:32:12 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_tree	*cr_tree(void)
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

t_cmd	*cr_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		perror("Allocation Error");
		exit(EXIT_FAILURE);
	}
	new_cmd->args = NULL;
	new_cmd->redir_list = NULL;
	return (new_cmd);
}

void	push_cmd_to_tree(t_tree **tree, t_cmd *cmd)
{
	t_tree	*new_tree;

	new_tree = cr_tree();
	new_tree->type = CMD_NODE;
	new_tree->cmd_node = cmd;
	*tree = new_tree;
}

void	cr_and_expand_tree(t_tree **tree, t_token **tokens)
{
	t_cmd	*cmd;
	t_tree	*new_tree;
	t_tree	*current;

	if (!(*tree))
	{
		cmd = cr_cmd_node(tokens);
		push_cmd_to_tree(tree, cmd);
	}
	else
	{
		current = (*tree);
		new_tree = cr_tree();
		new_tree->type = PIPE_NODE;
		new_tree->left = (*tree);
		cmd = cr_cmd_node(tokens);
		push_cmd_to_tree(&(new_tree)->right, cmd);
		(*tree) = new_tree;
	}
}

t_tree	*lets_parse(t_token **tokens)
{
	t_tree	*tree;
	t_cmd	*cmd;
	t_token	*tmp;

	tree = NULL;
	cmd = NULL;
	tmp = (*tokens);
	while (tmp)
	{
		cr_and_expand_tree(&tree, &tmp);
		if (tmp)
			tmp = tmp->next;
	}
	free_tokens(tokens);
	return (tree);
}
