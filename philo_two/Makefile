NAME = philo_two

CFLAGS  = -Wall -Wextra -Werror 

OBJ_PATH = ./obj

SRCS = 	philo_two.c \
		utils.c \
		utils_print.c \
		ft_init.c \
		destroy.c \
		routine.c \

OBJ_NAME = $(SRCS:.c=.o)


$(NAME) : $(OBJ_NAME)
	@rm -rf $(NAME)
	@gcc $(CFLAGS) -o $(NAME) -I philo_two.h $(OBJ_NAME) -Wall -Wextra -Werror -g -lpthread
	@echo "\033[33m[Done !]"


all : $(NAME)

clean :
	rm -rf $(OBJ_NAME) 

fclean : clean
	rm -rf $(NAME)

re : fclean all