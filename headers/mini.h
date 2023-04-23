/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:22 by kslik             #+#    #+#             */
/*   Updated: 2023/04/23 16:34:03 by aessaoud         ###   ########.fr       */
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

//enums
typedef enum e_tree_type
{
	CMD_NODE = 'C',
	PIPE_NODE = 'P',
}	t_tree_type;

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

typedef enum e_quotes
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	CLOSED_QUOTE,
}	t_quotes;

// structs

typedef struct s_token_info
{
	int			i;
	int			line;
	int			br;
	t_quotes	quote_stat;
	int			s_index;
	int			size;
}	t_token_info;

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



typedef struct s_red_list
{
	char	*file_out;
}	t_red_list;

typedef struct s_cmd
{
	char	**args;
	int		fd_out;
	
}	t_cmd;

typedef struct s_tree
{
	t_tree_type		type;
	struct s_cmd	*cmd_node;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;



void	add_token(t_token **head, char *s, int s_index, int size, enum e_token type);
t_token	*lets_tokenize(char *line);
int empty_command(char *input);

char 	*closeDOUBLE_QUOTE(char *line);
void	lets_parse(t_token **tokens);
void    print_tokens(t_token *head);
void	print_my_tree(t_tree *tree);

int		check_add_pipe_token(t_token **head, char *line, t_token_info *token_info);
int	check_add_heredoc_token(t_token **head, char *line, t_token_info *token_info);
int	check_add_red_append_token(t_token **head, char *line, t_token_info *token_info);
int	check_add_red_out_token(t_token **head, char *line, t_token_info *token_info);
int	check_add_red_inp_token(t_token **head, char *line, t_token_info *token_info);
#endif
