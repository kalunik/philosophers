CC	=	gcc
RM	=	rm -f
CFLAGS	=	-I. -Wall -Wextra -Werror
NAME	=	philo
SRCS	=	philo.c \
            ft_atoi.c \
            life_cycle.c \
            parse_args.c \
            utils.c

OBJS	=	$(patsubst %.c, %.o, $(SRCS))

all:
			@$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			@$(CC) -o $(NAME) $(OBJS)
			@echo "philo is ready to use ✅ "

%.o: %.c	philo.h
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM)	$(OBJS)
			@echo ".o Deleted 🗿"

fclean: 	clean
			@$(RM)	 $(NAME)
			@echo "Deleted 😬"

re:			fclean all

.PHONY: all clean fclean re