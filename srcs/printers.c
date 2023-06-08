/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:46:01 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/08 17:39:00 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//anms7oha mn b3da hah
void	print_tokens(t_token *head)
{
	//anms7oha mn b3da hah
	while (head)
	{
		printf("arg : %-10s", head->s);
		if (head->type == WORD)
			printf("TYPE : WORD\n");
		if (head->type == ENV)
			printf("TYPE : ENV\n");
		if (head->type == RED_INPUT)
			printf("TYPE : <\n");
		if (head->type == RED_OUTPUT_APPEND)
			printf("TYPE : >>\n");
		if (head->type == RED_OUTPUT)
			printf("TYPE : >\n");
		if (head->type == HEREDOC)
			printf("TYPE : <<\n");
		if (head->type == PIPE)
			printf("TYPE : |\n");
		if (head->type == EXIT_STATUS)
			printf("TYPE : EXIT_CODE\n");
		head = head->next;
	}
}

void	print_my_tree(t_tree *tree)
{
	int	i;

	if (!tree)
		return ;
	if (tree->type == CMD_NODE)
	{
		i = -1;
		printf("%p - type : %c\n", tree, tree->type);
		printf("commands args : \n");
		while (tree->cmd_node->args && tree->cmd_node->args[++i])
		{
			printf("[%s] ", tree->cmd_node->args[i]);
		}
		//anms7oha mn b3da hah
		printf("\nRedirection List:\n");
		{
			while (tree->cmd_node->redir_list)
			{
				printf("file_name: %s | type : %c\n", tree->cmd_node->redir_list->file_name,
					tree->cmd_node->redir_list->type);
				if (tree->cmd_node->redir_list->here_doc_text)
					printf("heredoc text \n%s\n", tree->cmd_node->redir_list->here_doc_text);
				tree->cmd_node->redir_list = tree->cmd_node->redir_list->next;
			}
		}
		printf("\n------------------------------\n");
	}
	else
	{
		printf("%p - left %p - right %p - type %c\n", tree, tree->left, tree->right, tree->type);
		print_my_tree(tree->left);
		print_my_tree(tree->right);
	}
	//anms7oha mn b3da hah
}
