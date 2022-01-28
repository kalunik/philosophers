CC	=	gcc
RM	=	rm -f
CFLAGS	=	-I. -Wall -Wextra -Werror
NAME_B	=	philo_bonus
SRCS_B	=	philo_bonus.c \
            ft_atoi.c \
            life_cycle_bonus.c \
            monitoring.c \
            parse_args_bonus.c \
            utils_bonus.c

OBJS_B	=	$(patsubst %.c, %.o, $(SRCS_B))

all:
			@$(MAKE) $(NAME_B)

bonus:
			@$(MAKE) $(NAME_B)

$(NAME_B):	$(OBJS_B)
			@$(CC) -o $(NAME_B) $(OBJS_B)
			@echo "philo_bonus is ready to use ✅ "

%.o: %.c	philo_bonus.h
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM)	$(OBJS_B)
			@echo ".o Deleted 🗿"

fclean: 	clean
			@$(RM)	 $(NAME_B)
			@echo "Deleted 😬"

re:			fclean all

.PHONY: all clean fclean re