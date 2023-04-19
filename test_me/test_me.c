#include "test_header.h"


// void	sir(t_tree **tree, int c, char t)
// {
// 	t_cmd	*cmd;
// 	if (c == 0)
// 		return ;
// 	if (t == 'c')
// 	{
// 		add_node(&cmd, 10);
// 		if (!*tree)
// 			*tree = cmd;
// 		else
// 		{
// 			t_cmd	
// 		}
// 	}
// }

int main(int c, char **argv)
{
	// t_ast_root	*root;
	t_tree	*tree;

	push_cmd_to_tree(&tree, 10);
	push_cmd_to_tree(&tree, 20);
	push_cmd_to_tree(&tree, 30);
	push_pipe_to_tree(&tree, 1);
	push_pipe_to_tree(&tree, 0);

	while (tree)
	{
		if (tree->type == 'c')
			printf("add: %-10p | next: %-10p | type: %-10c\n", tree, tree->next, tree->type);
		else
		{
			printf("add: %-10p | next: %-10p | type: %-10c\n", tree, tree->next, tree->type);
			printf("pipe left : %-10p | pipe right : %-10p\n", tree->pipe->left, tree->pipe->right);
		}
		printf("--------------------------------------\n");
		tree = tree->next;
	}

}