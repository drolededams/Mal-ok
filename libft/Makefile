# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 12:05:12 by dgameiro          #+#    #+#              #
#    Updated: 2016/12/16 16:08:45 by dgameiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_isdigit.c    ft_memcpy.c     ft_putendl_fd.c ft_strclr.c     ft_striteri.c   ft_strncmp.c    ft_strstr.c  ft_isprint.c    ft_memdel.c     ft_putnbr.c     ft_strcmp.c     ft_strjoin.c    ft_strncpy.c    ft_strsub.c ft_atoi.c       ft_itoa.c       ft_memmove.c    ft_putnbr_fd.c  ft_strcpy.c     ft_strlcat.c    ft_strnequ.c    ft_strtrim.c ft_bzero.c      ft_memalloc.c   ft_memset.c     ft_putstr.c     ft_strdel.c     ft_strlen.c     ft_strnew.c     ft_tolower.c ft_isalnum.c    ft_memccpy.c    ft_putchar.c    ft_putstr_fd.c  ft_strdup.c     ft_strmap.c     ft_strnstr.c    ft_toupper.c ft_isalpha.c    ft_memchr.c     ft_putchar_fd.c ft_strcat.c     ft_strequ.c     ft_strmapi.c    ft_strrchr.c ft_isascii.c    ft_memcmp.c     ft_putendl.c    ft_strchr.c     ft_striter.c    ft_strncat.c    ft_strsplit.c	ft_lstnew.c		ft_lstdelone.c		ft_lstdel.c		ft_lstadd.c		ft_lstiter.c	ft_lstmap.c		ft_convert_base.c	ft_strrev.c		ft_range.c		ft_max.c		ft_min.c	ft_power.c	ft_sqrt.c	ft_poschar.c	ft_ishexa.c get_next_line.c		ft_atof.c
OBJ = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
		@gcc $(FLAGS) $(SRCS) -c -I ./includes
		@ar rc  $(NAME) $(OBJ) 
	   	@ranlib $(NAME)	

clean:
		@rm -f $(OBJ)

fclean: clean
		@rm -f $(NAME)

re: fclean all

