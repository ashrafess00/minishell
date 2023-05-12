/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:47:55 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/12 12:26:51 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


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

void	enter_a_pipe(t_tree **tree)
{
	char	*line;
	t_token	*token;

	line = readline("pipe>");
	token = lets_tokenize(line);
	cr_and_expand_tree(tree, &token);
	free_tokens(&token);
}

t_tree	*lets_parse(t_token **tokens)
{
	t_tree	*tree;
	t_cmd	*cmd;
	char	l_r;
	t_token	*tmp;

	tree = NULL;
	cmd = NULL;
	tmp = (*tokens);
	while (tmp)
	{
		cr_and_expand_tree(&tree, &tmp);
		if (tmp && tmp->type == PIPE && !tmp->next)
			enter_a_pipe(&tree);
		if (tmp)
			tmp = tmp->next;
	}
	free_tokens(tokens);
	return (tree);
}