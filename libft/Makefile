# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rasaboun <rasaboun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 15:37:01 by rasaboun          #+#    #+#              #
#    Updated: 2019/11/11 13:42:37 by rasaboun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

SRC = ft_isdigit.c ft_memmove.c ft_split.c  ft_strmapi.c ft_toupper.c \
ft_atoi.c ft_isprint.c ft_memset.c ft_strchr.c  ft_strncmp.c \
ft_bzero.c ft_itoa.c ft_strdup.c ft_strnstr.c ft_calloc.c ft_iswhitespace.c \
ft_memccpy.c ft_putchar_fd.c ft_strjoin.c ft_strrchr.c ft_isalnum.c \
ft_memchr.c ft_putendl_fd.c ft_strlcat.c ft_strtrim.c ft_isalpha.c \
ft_memcmp.c ft_putnbr_fd.c  ft_strlcpy.c ft_substr.c ft_isascii.c \
ft_memcpy.c ft_putstr_fd.c ft_strlen.c ft_tolower.c ft_strcmp.c ft_strfjoin.c

SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

all: $(NAME)

OBJ=$(SRC:.c=.o)

OBJ_BONUS=$(SRC_BONUS:.c=.o)

bonus: $(OBJ_BONUS) $(OBJ)
	ar cr $(NAME) $(OBJ) $(OBJ_BONUS)
	ranlib $(NAME)

$(NAME): $(OBJ)
	ar cr $(NAME) $(OBJ)
	ranlib $(NAME)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all