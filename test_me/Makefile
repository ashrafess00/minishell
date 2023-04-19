NAME = test
CC = cc
CFLAGS = -Werror -Wextra -Wall
SRCS = test_me.c utils.c
LIBFT_DIR = ../libft/
LIBFT_A	= $(LIBFT_DIR)libft.a
OBJS_DIR = objs/
HEADERS = headers/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
INCLUDE = -I$(LIBFT_DIR)
RM = rm -rf

all: ${OBJS_DIR} ${NAME} 

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(OBJS) $(INCLUDE) $(LIBFT_A) -o $(NAME) -lreadline

$(OBJS_DIR)%.o: %.c
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