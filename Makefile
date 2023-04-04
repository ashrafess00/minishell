OBJECTS	= main.c
DEPO = mini.h
OUZ	= $(OBJECTS:.c=.o)
CFLAGS	= -Werror -Wextra -Wall
NAME	= shell
CC = cc

$(NAME):	$(OUZ)
	$(CC) $^ -o $(NAME) -lreadline
all:	${NAME} 

clean:
	rm -rf ${OUZ}
fclean:
	rm -rf ${OUZ} ${NAME}