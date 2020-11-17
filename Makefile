

INC=%%%%

INCLIB=$(INC)/../lib

CC=gcc

CFLAGS= -I$(INC) -O3 -I..

NAME= mlx-test
SRC = raycast.c test.c parsemap.c recup.c bmp.c get_next_line.c get_next_line_utils.c
srcc= test.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
objj = $(srcc:.c=.o)
all	:$(NAME)

$(NAME)	:$(OBJ) libft
	$(CC)  -o $(NAME)  $(OBJ) libft/libft.a -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd -g

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
