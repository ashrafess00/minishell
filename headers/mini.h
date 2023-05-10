/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:22 by kslik             #+#    #+#             */
/*   Updated: 2023/05/10 17:00:23 by aessaoud         ###   ########.fr       */
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

# define PERMISSION_MSG ": permission denied"
# define FILE_NOT_FOUND_MSG ": No such file or directory"
# define COMMAND_NOT_FOUND ": command not found"
# define STATUS_1 1
# define STATUS_126 126
# define STATUS_127 127

//enums
typedef enum e_tree_type
{
	CMD_NODE = 'C',
	PIPE_NODE = 'P',
}	t_tree_type;
typedef enum e_special_char
{
	NORMAL = 'a',
	RED_OUTPUT = '>',
	RED_INPUT = '<',
	ENV = '$',
	PIPE = '|',
	EXIT_STATUS,
	RED_OUTPUT_APPEND,
	HEREDOC,
}	t_special_char;

typedef enum e_quotes
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	CLOSED_QUOTE,
}	t_quotes;

// structs
typedef struct s_token_info_norm
{
	int			i;
	int			line;
	int			br;
	t_quotes	quote_stat;
	int			s_index;
	int			size;
}	t_token_info_norm;

typedef struct s_token
{
	char			*s;
	int 			s_index;
	// int				size;
	t_special_char	type;
	struct s_token	*next;
	// struct s_token *prev;
}	t_token;

typedef struct s_redir_list
{
	char				*file_name;
	int					type;
	char				*here_doc_text;
	struct s_redir_list	*next;
}	t_redir_list;

typedef struct s_cmd
{
	char				**args;
	struct s_redir_list	*redir_list;
}	t_cmd;

typedef struct s_tree
{
	t_tree_type		type;
	struct s_cmd	*cmd_node;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;


//tokenization
void	add_token(t_token **head, char *s, int s_index, int size, t_special_char type);
t_token	*lets_tokenize(char *line);
char 	*closeDOUBLE_QUOTE(char *line);

//parsing
// t_tree	*lets_parse(t_token **tokens);
t_tree	*lets_parse(t_token **tokens);

//utils
char	**my_env(char **nature);
int		stln(char **nature, int i);
char	**our_realloc(char **arr, char *new);


int		check_add_pipe_token(t_token **head, char *line, t_token_info_norm *token_info_norm);
int	check_add_heredoc_token(t_token **head, char *line, t_token_info_norm *token_info_norm);
int	check_add_red_append_token(t_token **head, char *line, t_token_info_norm *token_info_norm);
int	check_add_red_out_token(t_token **head, char *line, t_token_info_norm *token_info_norm);
int	check_add_red_inp_token(t_token **head, char *line, t_token_info_norm *token_info_norm);


//===execution===
void	lets_execute(t_tree *tree, char **env, int is_single_cmd);
void	redirect_it(t_tree *tree, int redirect);
//path
char	*get_path(char *program, char **paths);
char	**get_path_from_env(char **env);
void	write_error(char *file1, char *msg, int exit_status);

//close_fds
void	close_fds(int fds[8], int fds_count, ...);
void	close_fds_from_parent(int *fds, int fds_count, int fd_i);

//open files
int	open_outfile(char *file);
int	open_outfile_append(char *file);
int	open_infile(char *file);

//print_linked_lists
void	print_tokens(t_token *head);
void	print_my_tree(t_tree *tree);

//utils
int		ft_strcmp(char *s, char *limiter);

//free_me
void	free_arr(char **arr);
void	free_tokens(t_token **tokens_head);
void	free_tree(t_tree **tree);

//built_ins
int		is_built_in(t_tree *tree);
void	call_built_in(t_tree *tree, char **env);
void	my_cd(t_tree *tree);
void	my_echo(t_tree *tree);
void	my_exit(t_tree *tree);
void	my_export(t_tree *tree, char **env);
void	my_unset(t_tree *tree, char **env);
void	my_pwd(t_tree *tree);




#endif

