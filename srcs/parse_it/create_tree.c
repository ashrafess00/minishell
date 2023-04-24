/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:47:55 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/24 17:04:54 by aessaoud         ###   ########.fr       */
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
	// new_cmd->fd_out = -999;
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

int	open_out_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	open_in_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0644);
	return (fd);
}

int	open_out_append_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

static char	*get_input_from_usr(char *limiter)
{
	char	*input;
	char	*s;

	input = ft_calloc(1, 1);
	while (1)
	{
		ft_printf(">");
		s = get_next_line(0);
		if (!ft_strcmp(s, limiter))
			break ;
		input = ft_strjoin(input, s);
	}
	free(s);
	return (input);
}

t_redir_list	*cr_redir_list_node(char *file_name, int type)
{
	t_redir_list	*new_redir_list;

	new_redir_list = malloc(sizeof(t_redir_list));
	if (type == 1)
		new_redir_list->fd = open_out_file(file_name);
	else if(type == 2)
		new_redir_list->fd = open_in_file(file_name);
	else if(type == 3)
		new_redir_list->fd = open_out_append_file(file_name);
	else if (type == 4)
	{
		get_input_from_usr(file_name);
	}
	new_redir_list->file_name = file_name;
	new_redir_list->type = type;
	new_redir_list->next = NULL;
	return (new_redir_list);
}

void	add_redir_list_node(t_redir_list **head, char *file_name, int type)
{
	t_redir_list	*temp;

	if (!(*head))
		(*head) = cr_redir_list_node(file_name, type);
	else
	{
		temp = cr_redir_list_node(file_name, type);
		temp->next = (*head);
		(*head) = temp;
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
			add_redir_list_node(&cmd->redir_list, (*tokens)->s, 1);
		}
		else if ((*tokens)->type == RED_INPUT)
		{
			*tokens = (*tokens)->next;
			add_redir_list_node(&cmd->redir_list, (*tokens)->s, 2);
		}
		else if ((*tokens)->type == RED_OUTPUT_APPEND)
		{
			*tokens = (*tokens)->next;
			add_redir_list_node(&cmd->redir_list, (*tokens)->s, 3);
		}
		else if ((*tokens)->type == HEREDOC)
		{
			*tokens = (*tokens)->next;
			add_redir_list_node(&cmd->redir_list, (*tokens)->s, 4);
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

void	enter_a_pipe(t_tree **tree)
{
	char	*line;
	t_token	*token;

	line = readline("pipe>");
	token = lets_tokenize(line);
	cr_and_expand_tree(tree, &token);

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
		if ((*tokens) && (*tokens)->type == PIPE && !(*tokens)->next)
			enter_a_pipe(&tree);
		if ((*tokens))
			*tokens = (*tokens)->next;
	}
	print_my_tree(tree);
}