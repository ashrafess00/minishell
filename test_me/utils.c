#include "test_header.h"

t_cmd	*cr_cmd(int a)
{
	t_cmd	*new_cmd = malloc(sizeof(t_cmd));

	new_cmd->a = a;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_node(t_cmd **head, int a)
{
	t_cmd	*tmp;

	if (!*head)
		*head = cr_cmd(a);
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cr_cmd(a);
	}
}

t_tree	*cr_tree()
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	tree->cmd = NULL;
	tree->pipe = NULL;
	tree->next = NULL;
	return (tree);
}

//put command node in the tree then push
void	push_cmd_to_tree(t_tree **tree, int a)
{
	t_tree	*new_tree;
	
	new_tree = cr_tree();
	new_tree->type = 'c';
	new_tree->cmd = cr_cmd(a);

	if (!*tree)
		*tree = new_tree;
	else
	{
		new_tree->next = (*tree);
		*tree = new_tree;
	}
}

void	push_pipe_to_tree(t_tree **tree, int l)
{
	t_tree	*new_tree;
	t_tree	*current;

	current = *tree;
	new_tree = cr_tree();
	new_tree->type = 'p';
	new_tree->next = NULL;

	if (l == 1)
	{
		new_tree->pipe = malloc(sizeof(t_pipe));
		new_tree->pipe->left = current;
	}
	else
	{
		new_tree->pipe = malloc(sizeof(t_pipe));
		new_tree->pipe->right = current;
	}


	if (!*tree)
		*tree = new_tree;
	else
	{
		new_tree->next = (*tree);
		*tree = new_tree;
	}
}