CC	=	gcc
RM	=	rm -f
CFLAGS	=	-I./includes -Wall -Wextra -Werror
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

#bonus:
#			@$(MAKE) -C $(LIBFT)
#			@$(MAKE) $(B_NAME)
#
#$(B_NAME):	$(B_OBJS) $(LIBFT)/libft.a libft/libft.h
#			@$(CC) -o $(B_NAME) $(B_OBJS)
#			@echo "philo_bonus is ready to use ✅ "

%.o: %.c	includes/so_long.h get_next_line/get_next_line.h
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM)	$(OBJS) #$(B_OBJS)
			@echo ".o Deleted 🗿"

fclean: 	clean
			@$(RM)	 $(NAME) #$(B_NAME)
			@echo "Deleted 😬"

re:			fclean all

.PHONY: all clean fclean re