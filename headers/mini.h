/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:22 by kslik             #+#    #+#             */
/*   Updated: 2023/04/20 18:04:55 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include "libft.h"
# define S_QUOTE '\''
# define D_QUOTE '\"'

enum e_token
{
	NORMAL = 'a',
	RED_OUTPUT = '>',
	RED_INPUT = '<',
	ENV = '$',
	PIPE = '|',
	SPACE = ' ',
	EXIT_STATUS,
	RED_OUTPUT_APPEND,
	HEREDOC,
};

typedef enum e_tree_type
{
	CMD,
	PIPE_NODE,
}	t_tree_type;

typedef struct s_token
{
	char			*s;
	int 			s_index;
	int				size;
	enum e_token	type;
	char			**envs;
	struct s_token	*next;
	struct s_token *prev;
}	t_token;

typedef struct s_cmd
{
	char	**args;
}	t_cmd;

typedef struct s_tree
{
	t_tree_type	type;
	struct s_tree	*next;
	// struct s_pipe	*pipe_node;
	struct s_cmd	*cmd_node;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

void	cr_token(t_token **head, char *s, int s_index, int size, enum e_token type);
// void	lets_tokenize(char *line);
t_token	*lets_tokenize(char *line);
int empty_command(char *input);

int	is_pipe(char *s, char q, int *error);
int is_heredoc(char *s, char q, int *error);
int is_red_input_append(char *s, char q, int *error);
int is_red_output(char *s, char q, int *error);
int is_red_input(char *s, char q, int *error);
int	is_env(t_token **head,  char *line, int *i, int *s_index, int size, char *q);
char *closed_quote(char *line);
// void	lets_parse(t_token *tokens);
void	lets_parse(t_token **tokens);
void    print_tokens(t_token *head);
#endif
