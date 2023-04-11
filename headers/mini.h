/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:22 by kslik             #+#    #+#             */
/*   Updated: 2023/04/11 21:16:43 by aessaoud         ###   ########.fr       */
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
	REDIRECT_OUTPUT = '>',
	REDIRECT_INPUT = '<',
	ENV = '$',
	PIPE = '|',
	EXIT_STATUS,
	REDIRECT_OUTPUT_APPEND,
	HEREDOC,
};

typedef struct s_token
{
	char			*s;
	int 			s_index;
	int				size;
	enum e_token	type;
	struct s_token	*next;
	struct s_token *prev;
}	t_token;

void	cr_token(t_token **head, char *s, int s_index, int size, enum e_token type);
void	lets_tokenize(char *line);
int empty_command(char *input);

int	is_pipe(char *s, char q);

#endif
