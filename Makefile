SRC	=	main.c
SRC	+=	philo.c
SRC	+=	death.c
SRC	+=	free_error.c
SRC	+=	init.c
SRC	+=	print.c
SRC	+=	tools.c
OBJ	=	$(SRC:.c=.o)
NAME	=	philo
CC	=	cc	
CFLAGS	= -Wall -Wextra -Werror
CFLAGS	= -lpthread
CFLAGS += -I.

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ) 
		$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)


re : fclean all

.PHONY : all clean fclean re