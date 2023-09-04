# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachen <yachen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 10:56:05 by yachen            #+#    #+#              #
#    Updated: 2023/09/04 10:56:17 by yachen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_B = pipex_bonus

CC = gcc

CFLAGS =  -Wall -Wextra -Werror -g

RM = rm -rf

SRC = pipex.c utils_1.c utils_2.c \

SRC_B = pipex_bonus.c utils_1.c utils_2.c utils_bonus.c \

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

bonus: $(NAME_B)

$(NAME): $(OBJ)
		@echo "\033[32m\n=============================="
		@make -C ./libft
		@echo "\033[32mCompiling pipex---------------"
		@$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)
		@echo "\033[32m----created with success : pipex"
		@echo "\033[32m==============================\n"

$(NAME_B): $(OBJ_B)
		@echo "\033[32m\n=============================="
		@make -C ./libft
		@echo "\033[32mCompiling pipex_bonus---------------"
		@$(CC) $(CFLAGS) $(OBJ_B) ./libft/libft.a -o $(NAME_B)
		@echo "\033[32m----Created with success : pipex_bonus"
		@echo "\033[32m==============================\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[32m\n=================="
	@echo "\033[32mCleaning Pipex----"
	@$(RM) $(OBJ) $(OBJ_B)
	@echo "\033[32m------Pipex Cleaned"
	@make clean -C ./libft
	@echo "\033[32m==================\n"

fclean:
	@echo "\033[32m\n=================="
	@echo "\033[32mCleaning Pipex----"
	@$(RM) $(OBJ) $(OBJ_B)
	@echo "\033[32m------Pipex Cleaned"
	@$(RM) $(NAME) $(NAME_B)
	@make fclean -C ./libft
	@echo "\033[32m==================\n"

re: fclean all

.PHONY: clean fclean all re bonus
