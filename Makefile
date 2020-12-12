

INC=%%%%

INCLIB=$(INC)/../lib

CC=gcc

CFLAGS= -I$(INC) -O3 -I..

NAME= mlx-test
SRC =  test.c parsemap.c recup.c bmp.c get_next_line.c get_next_line_utils.c
srcc= test.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
objj = $(srcc:.c=.o)
all	:$(NAME)

$(NAME)	:$(OBJ) libft
	$(CC) -g raycast.c ft_draw.c dda.c ft_draw_sprites.c key_manager.c test.c parsemap.c recup.c bmp.c get_next_line.c get_next_line_utils.c libft/libft.a -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

libft :
	cd libft/
	make bonus
clean	:
	rm -f $(NAME) $(OBJ) *~ core *.core

cleantest :
	rm test

test :
	$(CC) -o test $(srcc) ./libft/libft.a -fsanitize=address -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

re	: clean all
