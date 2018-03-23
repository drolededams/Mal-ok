# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 15:32:27 by dgameiro          #+#    #+#              #
#    Updated: 2018/03/23 12:09:06 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c src/free.c src/init.c src/malloc.c src/zone.c src/realloc.c \
src/print.c src/print_hex.c src/alloc.c src/lib_free.c src/lib_real.c \
src/lib_print.c src/lib_print_b.c

INC = -I./inc

NAME = Malloc

FLAGS = -Wall -Werror -Wextra


$(NAME):
	@make -C ./libft
	@gcc $(FLAGS) $(SRC) $(INC) -L libft/ -lft -o $(NAME)

all: $(NAME)

clean :
	@make -C libft/ fclean

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
