# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 02:01:59 by user42            #+#    #+#              #
#    Updated: 2023/09/27 23:22:24 by rasaboun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		Cub3D
LIBFT	=		libft/libft.a
MLX		=		minilibx-linux/libmlx.a
CC		=		gcc
GREEN	=		'\033[0;32m'
SRC		=	src/raycast.c\
			src/utils/initray.c\
			src/utils/raypixel_utils.c \
			src/utils/raycastchoose.c \
			src/utils/parse_utils.c\
			src/utils/error_utils.c \
			src/utils/key_manager_utils.c\
			src/utils/color_utils.c \
			src/utils/get_utils.c \
			src/utils/recup_utils.c \
			src/utils/free_utils.c \
			src/utils/init_utils.c \
			src/utils/calcul_utils.c \
			src/ft_draw.c \
			src/dda.c \
			src/ft_draw_sprites.c \
			src/key_manager.c \
			src/error.c \
			src/parsemap.c \
			src/parsing.c \
			src/bmp.c \
			src/get_next_line.c \
			src/get_next_line_utils.c \
			src/utils/init.c

OBJS=$(SRC:.c=.o)

%.o: %.c
	$(CC) -I./include -o $@ -c $< 

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
		$(CC) $(OBJS) -I./include -I./libft -I./minilibx-linux -Wall -Werror -Wextra -L ./libft -lft -L ./minilibx-linux -lmlx -lm -lX11 -lXext -o $(NAME) -g
		@echo ${GREEN}FINI !

$(LIBFT):
		make bonus -s -C libft

$(MLX):
		make -s -C minilibx-linux

clean:
		make clean -s -C libft
		make clean -s -C minilibx-linux
		rm -f $(OBJS)

fclean: clean
	make fclean -s -C libft
	rm -rf image.bmp
	rm -f $(NAME)

re: fclean all

bonus: all

.PONY: all clean fclean re bonus
