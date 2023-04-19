#ifndef TEST_HEADER_H
#define TEST_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <termios.h>
#include "libft.h"

typedef struct s_cmd
{
	char			**args;
	int				a;
	int				b;
	struct s_cmd	*next;
	char	*test;
}	t_cmd;

typedef struct s_pipe
{
	struct s_tree	*right;
	struct s_tree	*left;
}	t_pipe;

typedef struct s_tree
{
	char				type;
	struct s_cmd	*cmd;
	struct s_pipe	*pipe;
	struct s_tree	*next;
}	t_tree;

typedef struct	s_ast_root
{
	struct s_tree	*root;
}	t_ast_root;

t_cmd	*cr_cmd(int a);
void	add_node(t_cmd **head, int a);
void	push_cmd_to_tree(t_tree **tree, int a);
void	push_pipe_to_tree(t_tree **tree, int l);
#endif