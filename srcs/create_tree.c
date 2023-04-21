/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:47:55 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/21 18:28:58 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_tree	*cr_tree()
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	tree->cmd_node = NULL;
	// tree->pipe_node = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->next = NULL;
	return (tree);
}

t_cmd	*cr_cmd()
{
	t_cmd	*new_cmd = malloc(sizeof(t_cmd));
	new_cmd->args = ft_calloc(100, sizeof(char *));
	return (new_cmd);
}


void	push_cmd_to_tree(t_tree **tree, t_cmd *cmd)
{
	t_tree	*new_tree;
	new_tree = cr_tree();
	new_tree->type = 'c';
	new_tree->cmd_node = cmd;
	if (!*tree)
		*tree = new_tree;
	else
	{
		new_tree->next = (*tree);
		*tree = new_tree;
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
		cmd->args[i] = ft_strdup((*tokens)->s);
		*tokens = (*tokens)->next;
		i++;
	}
	// if ((*tokens) && (*tokens)->type == PIPE)
	// 	*tokens = (*tokens)->next;
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
		// printf("hi1\n");
		cmd = cr_cmd_node(tokens);
		push_cmd_to_tree(tree, cmd);
	}
	else
	{
		// printf("hi2\n");
		current = (*tree);
		
		new_tree = cr_tree();
		new_tree->left = (*tree);
		
		cmd = cr_cmd_node(tokens);
		push_cmd_to_tree(&(new_tree)->right, cmd);
		(*tree) = new_tree;
	}
	
}

void	print_my_tree(t_tree *tree)
{
	int	i;

	if (!tree)
		return ;
	if (tree->type == 'c')
	{
		i = -1;
		printf("%p\n", tree);
		printf("commands args : \n");
		while (tree->cmd_node->args[++i])
		{
			printf("[%s] ", tree->cmd_node->args[i]);
		}
		printf("\n------------------------------\n");
	}
	else
	{
		printf("%p - left %p - right %p\n", tree, tree->left, tree->right);
		print_my_tree(tree->left);
		print_my_tree(tree->right);
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