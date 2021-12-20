CC	=	gcc
RM	=	rm -f
CFLAGS	=	-I./includes -Imlx -Wall -Wextra -Werror
NAME	=	philo
LIBFT	=	./libft
SRCS	=

OBJS	=	$(patsubst %.c, %.o, $(SRCS))

all:
			@$(MAKE) -C $(LIBFT)
			@$(MAKE) $(NAME)

$(NAME):	$(OBJS) $(LIBFT)/libft.a libft/libft.h
#			$(MLX_LIB)
			@$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) $(LIBFT)/libft.a
			@echo "so_long is ready to use ✅ "

bonus:
			@$(MAKE) -C $(LIBFT)
			@$(MAKE) $(B_NAME)

$(B_NAME):	$(B_OBJS) $(LIBFT)/libft.a libft/libft.h
			@$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(B_NAME) $(B_OBJS) $(LIBFT)/libft.a
			@echo "so_long_bonus is ready to use ✅ "

%.o: %.c	includes/so_long.h get_next_line/get_next_line.h
			@$(CC) $(CFLAGS) -c $< -o $@

#$(MLX_LIB):
#			$(MAKE) -C $(MLX_DIR)
#			@cp $(MLX_DIR)/$(MLX_LIB) ./$(MLX_LIB)

clean:
			@$(MAKE) -C $(LIBFT)/ clean
			@$(RM)	$(OBJS) $(B_OBJS)
			@echo ".o Deleted 🗿"

fclean: 	clean
			@$(MAKE) -C $(LIBFT)/ fclean
#			@$(MAKE) -C mlx/ clean
			@$(RM)	 $(NAME) $(B_NAME)
			@echo "Deleted 😬"

re:			fclean all

.PHONY: all clean fclean re