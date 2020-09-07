

INC=%%%%

INCLIB=$(INC)/../lib

CC=gcc

CFLAGS= -I$(INC) -O3 -I..

NAME= mlx-test
SRC = raycast.c test.c get_next_line.c get_next_line_utils.c ./libft/libft.a
srcc= test.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
objj = $(srcc:.c=.o)
all	:$(NAME)

$(NAME)	:$(OBJ)
	$(CC) -o $(NAME)  $(OBJ) -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd -g

clean	:
	rm -f $(NAME) $(OBJ) *~ core *.core

cleantest :
	rm test

test : 
	$(CC) -o test $(srcc) ./libft/libft.a -fsanitize=address -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

re	: clean all
