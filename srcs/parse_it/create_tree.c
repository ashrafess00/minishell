/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:47:55 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/23 12:01:12 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_tree	*cr_tree()
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	tree->cmd_node = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_cmd	*cr_cmd()
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->args = ft_calloc(100, sizeof(char *));
	new_cmd->fd_out = -999;
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

int	open_out_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_TRUNC, 0644);
	return (fd);
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
			cmd->fd_out = open_out_file((*tokens)->s);
		}
		else
		{
			cmd->args[i] = ft_strdup((*tokens)->s);
			i++;
		}
		*tokens = (*tokens)->next;
	}
	return (cmd);
}


void	cr_and_expand_tree(t_tree **tree, t_token **tokens)
{
	t_cmd	*cmd;
	t_tree	*temp;
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

void	lets_parse(t_token **tokens)
{
	t_tree	*tree;
	t_cmd	*cmd;
	char	l_r;

	tree = NULL;
	cmd = NULL;
	l_r = 0;
	while (*tokens)
	{
		cr_and_expand_tree(&tree, tokens);
		if ((*tokens))
			*tokens = (*tokens)->next;
	}
	print_my_tree(tree);
}