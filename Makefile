NAME = shell
CC = cc
CFLAGS = -Werror -Wextra -Wall
SRCS_DIR = srcs/
SRCS = main.c parsing_funcs.c check_tokens.c helpers.c check_syn_error.c create_tree.c
LIBFT_DIR = libft/
LIBFT_A	= $(LIBFT_DIR)libft.a
DEPO = mini.h
OBJS_DIR = objs/
HEADERS = headers/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
INCLUDE = -I$(HEADERS) -I$(LIBFT_DIR)
RM = rm -rf

all: ${OBJS_DIR} ${NAME}

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS) $(LIBFT_A) $(HEADERS)*
	$(CC) $(OBJS) $(INCLUDE) $(LIBFT_A) -o $(NAME) -lreadline

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(INCLUDE) -c -o $@ $^

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) ${OBJS_DIR}
	make clean -C $(LIBFT_DIR)
fclean:
	$(RM) ${OBJS_DIR} ${NAME}
	make fclean -C $(LIBFT_DIR)
re: fclean all