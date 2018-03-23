# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 15:32:27 by dgameiro          #+#    #+#              #
#    Updated: 2018/03/23 18:51:59 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Ilibft -Iinc -Wall -Wextra -Werror
SRC = main.c free.c init.c malloc.c zone.c realloc.c \
print.c print_hex.c alloc.c lib_free.c lib_real.c \
lib_print.c lib_print_b.c lib_print_hex.c lib_print_hex_b.c

OBJDIR = objs
VPATH = srcs

OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.c=.o))

NAME = malloc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) -Llibft/ -lft -o $@ $^


$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

clean :
	@make clean -C libft
	@rm -rf $(OBJDIR)

fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)

re : fclean all
