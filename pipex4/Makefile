# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 10:56:05 by yachen            #+#    #+#              #
#    Updated: 2023/08/24 14:12:35 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

SRC = main.c utils.c lst_error.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@make -C ./libft
		$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	cd ./libft && make clean

fclean: clean
	$(RM) $(NAME)
	cd ./libft && make fclean

re: fclean all

.PHONY: clean fclean all re
