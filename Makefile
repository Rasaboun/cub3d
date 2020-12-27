# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 02:01:59 by user42            #+#    #+#              #
#    Updated: 2020/12/27 19:39:41 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		Cub3D
LIBFT	=		libft/libft.a
MLX		=		minilibx-linux/libmlx.a
CC		=		gcc
GREEN	=		'\033[0;32m'

SRC		=	raycast.c\
			utils/initray.c\
			utils/raypixel_utils.c \
			utils/raycastchoose.c \
			utils/parse_utils.c\
			utils/error_utils.c \
			utils/key_manager_utils.c\
			utils/color_utils.c \
			utils/get_utils.c \
			utils/recup_utils.c \
			utils/free_utils.c \
			utils/init_utils.c \
			utils/calcul_utils.c \
			ft_draw.c \
			dda.c \
			ft_draw_sprites.c \
			key_manager.c \
			test.c \
			parsemap.c \
			recup.c \
			bmp.c \
			get_next_line.c \
			get_next_line_utils.c \
			utils/init.c
		
OBJS=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
		$(CC) $(OBJS) -I . -I./libft -I./minilibx-linux -Wall -Werror -Wextra -L ./libft -lft -L ./minilibx-linux -lmlx -lbsd -lm -lX11 -lXext -o $(NAME) -g
		@echo ${GREEN}FINI !

$(LIBFT):
		make bonus -s -C libft

$(MLX):
		make -s -C minilibx-linux

clean:
		make clean -s -C libft
		make clean -s -C minilibx-linux
		rm $(OBJS)

fclean: clean
	make fclean -s -C libft
	rm -rf image.bmp

re: fclean all

bonus: all

.PONY: all clean fclean re bonus
