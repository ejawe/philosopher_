NAME = philo_one

CFLAGS  = -Wall -Wextra -Werror 

SRCS = 	philo_one.c \
		utils.c \
		utils_print.c \
		ft_init.c \
		destroy.c \
		routine.c \

OBJ_NAME = $(SRCS:.c=.o)


$(NAME) : $(OBJ_NAME)
	@rm -rf $(NAME)
	@gcc $(CFLAGS) -o $(NAME) -I philo_one.h $(OBJ_NAME) -Wall -Wextra -Werror -g -lpthread
	@echo "\033[33m[Done !]"


all : $(NAME)

clean :
	rm -rf $(OBJ_NAME) 

fclean : clean
	rm -rf $(NAME)

re : fclean all