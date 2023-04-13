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

enum e_chars
{
	WORD = -1,
	JI = 5,
};

typedef struct s_dl
{
	int 			num;
	enum e_chars	chars;
	struct s_dl		*next;
	struct s_dl 	*prev;
}   t_token;

#endif