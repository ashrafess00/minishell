NAME = shell
CC = cc
CFLAGS = -Werror -Wextra -Wall

# DIRECTORIES
SRCS_DIR = srcs/
TOKENIZE_IT_DIR = $(SRCS_DIR)tokenize_it/
PARSE_IT_DIR = $(SRCS_DIR)parse_it/
LIBFT_DIR = libft/
OBJS_DIR = objs/
HEADERS = headers/

# SRCS
TOKENIZE_IT_SRCS = check_syn_error.c  add_special_chars_tokens.c tokenizing_funcs.c create_tokens.c
PARSE_IT_SRCS = create_tree.c
SRCS = main.c helpers.c  $(TOKENIZE_IT_SRCS) $(PARSE_IT_SRCS)


LIBFT_A	= $(LIBFT_DIR)libft.a
DEPO = mini.h

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

$(OBJS_DIR)%.o: $(TOKENIZE_IT_DIR)%.c
	$(CC) $(INCLUDE) -c -o $@ $^

$(OBJS_DIR)%.o: $(PARSE_IT_DIR)%.c
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