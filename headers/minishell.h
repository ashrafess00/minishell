/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:22 by kslik             #+#    #+#             */
/*   Updated: 2023/05/30 16:17:59 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include "libft.h"
# define PERMISSION_MSG ": Permission denied"
# define FILE_NOT_FOUND_MSG ": No such file or directory"
# define COMMAND_NOT_FOUND ": command not found"
# define IS_A_DIRECTORY ": is a directory"
# define NOT_A_VALID_INDENTIFIER ": not a valid identifier"
# define STATUS_1 1
# define STATUS_126 126
# define STATUS_127 127
# define REDIRECT 1
# define DONT_REDIRECT 0
//enums
typedef enum e_tree_type
{
	CMD_NODE = 'C',
	PIPE_NODE = 'P',
}	t_tree_type;

struct s_export
{
	int	i;
	int	j;
	int	k;
	int	fl;
	int	si;
	int	ps;
	int	retu;
	int	brak;
};

struct s_noopt
{
	int	i;
	int	j;
	int	fl;
	int	l;
	int	p;
	int	q;
};

typedef enum e_special_char
{
	WORD = 'a',
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
typedef struct s_tin
{
	int			i;
	int			line;
	int			br;
	t_quotes	quote_stat;
	int			s_index;
	int			size;
	int			special_char_found;
}	t_tin;

typedef struct s_token
{
	char			*s;
	int				s_index;
	t_special_char	type;
	struct s_token	*next;
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

typedef struct s_my_env
{
	char			*val;
	struct s_my_env	*next;
}	t_my_env;

struct s_unset
{
	int			i;
	int			si;
	t_my_env	*tmp;
	t_my_env	*prev;
};
struct s_echo
{
	int	i;
	int	pid;
	int	status;
};
struct s_expand
{
	int			i;
	int			c;
	t_my_env	*tmp;
	char		*result;
	int			result_index;
	char		pedi[200];
	int			position;
	int			fl;
	int			input_index;
	int			brek;
};
//tokenization
void	add_token(t_token **head, char *s, t_special_char type);
t_token	*lets_tokenize(char *line);
int		check_add_pipe_token(t_token **head, char *line, t_tin *tin);
int		check_add_heredoc_token(t_token **head, char *line, t_tin *tin);
int		check_add_red_append_token(t_token **head, char *line, t_tin *tin);
int		check_add_red_out_token(t_token **head, char *line, t_tin *tin);
int		check_add_red_inp_token(t_token **head, char *line, t_tin *tin);
int		check_tokens(t_token *tokens, int *exit_code);

//parsing
t_tree	*lets_parse(t_token **tokens, t_my_env *my_env);
t_tree	*cr_tree(void);
t_cmd	*cr_cmd(void);
t_cmd	*cr_cmd_node(t_token **tokens, t_my_env *my_env);

//=======execution=======
void	lets_execute(t_tree *tree, t_my_env **env,
			int is_single_cmd, int *exit_code);
void	redirect_it(t_tree *tree, int redirect);
char	*expandini(char *input, t_my_env *my_env, int exit_code);
void	free_pedi(char *pedi);
//path
char	*get_path(char *program, char **paths);
char	**get_path_from_env(char **env);
void	write_error(char *file1, char *msg, int exit_status);
int		is_a_directory(char *program);
//open files
int		open_outfile(char *file);
int		open_outfile_append(char *file);
int		open_infile(char *file);
//export 
char	**exp_no_opt(char **env);
char	**my_env_to_array(t_my_env **my_env);
void	deletenode(t_my_env **my_env, char *key);

//built_ins
int		is_built_in(t_tree *tree);
void	call_built_in(t_tree *tree, t_my_env **my_env, int *exit_code);
void	my_echo(t_tree *tree, int *exit_code);
void	my_exit(t_tree *tree, int *exit_code);
void	my_pwd(t_tree *tree, int *exit_code);
void	my_export(t_tree *tree, t_my_env **my_env, int *exit_code);
void	my_cd(t_tree *tree, int *exit_code);
// void	my_unset(t_tree *tree, t_my_env **my_env, int *exit_code);

//manage envs
char	**from_lk_to_arr(t_my_env **my_env);
void	copy_env(t_my_env **head, char **env);
void	add_my_env_node(t_my_env **head, char *env);
void	print_envs(t_my_env *my_env);
void	update_envs(t_my_env **my_env);

//========General========
//utils
int		ft_strcmp(char *s, char *limiter);
char	**expand_arr(char **arr, char *val);
char	*get_input_from_usr(char *limiter, t_my_env *my_env);
char	*get_cdir(int exit_code);
int		is_empty(char *input);
int		is_single_cmd(t_tree *tree);
char	*get_removed_quotes_str(char *s);

//utils
void	new_node(t_my_env **my_env, char *ljadid);
void	initialize_dt_2(struct s_export *info, int fl);
void	excpo_case_1(struct s_export *info, t_my_env *tmp,
			char *ljadid, int fl);
void	tmp_val(t_my_env *tmp, char *ljadid, struct s_export *info, int n);
void	update_node(t_my_env *t, char *ljadid, struct s_export *in);
int		ex_err(char *cmd, int c);
int		check_node_exist(t_my_env *tmp, char *key);
void	initialize_dt(struct s_export *info);
int		unset_err(char *cmd);
void	unsetdata(struct s_unset *unset, t_my_env **my_env, int n);
void	echo_dt(struct s_echo *echo, int c, int *exit_code);
void	echo_err(int *exit_code, int c);
void	ex_data(struct s_expand *exp);
void	calcul_c(char *input, struct s_expand *exp, int c, char *ex);
void	search_ky_2(struct s_expand *exp);
void	search_key(char *input, struct s_expand *exp, int c);
void	inist_to_zero(struct s_expand *exp, int c, char *input);

//free_me
void	free_arr(char **arr);
void	free_tokens(t_token **tokens_head);
void	free_tree(t_tree **tree);
void	free_my_env(t_my_env **my_env_head);
void	idont_know_what_mdoin(struct s_expand *exp, int c,
			char *input, t_my_env *my_env);
void	enter_a_pipe(t_token **tokens);
void	freenode(t_my_env *node);
void	ctrl_c_handler(int signum);

#endif
