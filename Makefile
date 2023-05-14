# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 16:42:29 by aessaoud          #+#    #+#              #
#    Updated: 2023/05/14 12:45:54 by aessaoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = shell
CC = cc
CFLAGS = -Werror -Wextra -Wall

# DIRECTORIES
SRCS_DIR = srcs/
TOKENIZE_IT_DIR = $(SRCS_DIR)tokenize_it/
PARSE_IT_DIR = $(SRCS_DIR)parse_it/
EXECUTE_IT_DIR = $(SRCS_DIR)execute_it/
LIBFT_DIR = libft/
OBJS_DIR = objs/
HEADERS = headers/

# SRCS
TOKENIZE_IT_SRCS = check_syn_error.c  add_special_chars_tokens.c tokenizing_funcs.c create_tokens.c
PARSE_IT_SRCS = create_tree.c cr_nodes.c
EXECUTE_IT_SRCS = execute.c path.c open_files.c redirections.c my_built_ins.c export.c
SRCS = main.c helpers.c utils.c utils2.c free_me.c manage_envs.c $(TOKENIZE_IT_SRCS) $(PARSE_IT_SRCS) $(EXECUTE_IT_SRCS)


LIBFT_A	= $(LIBFT_DIR)libft.a
DEPO = mini.h

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
INCLUDE = -I$(HEADERS) -I$(LIBFT_DIR)
RM = rm -rf

all: ${OBJS_DIR} ${NAME}

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(LIBFT_A) $(OBJS) $(HEADERS)*
	@$(CC) $(OBJS) $(INCLUDE) $(LIBFT_A) -o $(NAME) -lreadline 
	@echo "SHELL WAS CREATED"

	
	
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(INCLUDE) -c -o $@ $^
	@echo GENERATING $^
	
$(OBJS_DIR)%.o: $(TOKENIZE_IT_DIR)%.c
	@$(CC) $(INCLUDE) -c -o $@ $^
	@echo GENERATING $^

$(OBJS_DIR)%.o: $(PARSE_IT_DIR)%.c
	@$(CC) $(INCLUDE) -c -o $@ $^
	@echo GENERATING $^

$(OBJS_DIR)%.o: $(EXECUTE_IT_DIR)%.c
	@$(CC) $(INCLUDE) -c -o $@ $^
	@echo GENERATING $^

$(LIBFT_A):
	@echo "GENERATING libft.a..."
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) ${OBJS_DIR}
	@make clean -C $(LIBFT_DIR) 
	@echo OBJECT FILES DELETED
fclean:
	@$(RM) ${OBJS_DIR} ${NAME}
	@make fclean -C $(LIBFT_DIR)
	@echo OBJECT FILES AND SHELL PROGRAM WERE DELETED
	
re: fclean all