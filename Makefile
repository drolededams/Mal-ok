# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/12 15:32:27 by dgameiro          #+#    #+#              #
#    Updated: 2018/06/20 13:34:36 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

.PHONY: all, clean, fclean, re

SRC_PATH = srcs
SRC_NAME = free.c init.c malloc.c zone.c realloc.c \
print.c print_hex.c alloc.c lib_free.c lib_real.c \
lib_print.c lib_print_b.c lib_print_hex.c lib_print_hex_b.c print_ex.c \
lib_print_ex.c

OBJ_PATH = objs

CPPFLAGS = -Iinc

LDFLAGS = -Llibft
LDLIBS = -lft

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))


all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	ln -F -s $(NAME) libft_malloc.so
	$(CC) $(LDFLAGS) $(LDLIBS) -shared $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@make clean -C libft
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean : clean
	@make fclean -C libft
	@rm -fv $(NAME)
	@rm -fv libft_malloc.so

re : fclean all
