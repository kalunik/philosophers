CC	=	gcc
RM	=	rm -f
CFLAGS	=	-I. -ggdb3 #-Wall -Wextra -Werror
NAME_B	=	philo_bonus
SRCS_B	=	philo_b.c \
            ft_atoi.c \
            life_cycle_b.c \
            parse_args_b.c \
            utils_b.c

OBJS_B	=	$(patsubst %.c, %.o, $(SRCS_B))

all:
			@$(MAKE) $(NAME_B)

$(NAME_B):	$(OBJS_B)
			@$(CC) -o $(NAME_B) $(OBJS_B)
			@echo "philo_bonus is ready to use ✅ "

%.o: %.c	philo_b.h
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM)	$(OBJS_B)
			@echo ".o Deleted 🗿"

fclean: 	clean
			@$(RM)	 $(NAME_B)
			@echo "Deleted 😬"

re:			fclean all

.PHONY: all clean fclean re