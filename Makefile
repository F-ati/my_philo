NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror 

SRS = main.c philo_utils.c init.c simulation.c

OBJC =  $(SRS:.c=.o)

all : $(NAME) 

$(NAME) : $(OBJC) philo.h
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME)

clean :
	rm -rf $(OBJC)

fclean : clean
	rm -rf $(NAME)

re : fclean all
