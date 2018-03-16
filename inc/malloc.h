/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:40:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 13:48:04 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define T_RSIZE 1048576
# define S_RSIZE 8388608
# define T_MSIZE 512
# define S_MSIZE 15360
# define TINY 1
# define SMALL 2
# define LARGE 3
# define T_HEAD g_alloc.tiny
# define S_HEAD g_alloc.small
# define L_HEAD g_alloc.large
# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h> 
# include <sys/resource.h>
# include <sys/mman.h>

typedef struct	s_block
{
	size_t		size;
	int			free;
	struct s_block *next;
	struct s_block *prev;
}				t_block;

typedef struct s_zone
{
	t_block		*head;
	t_block		*tail;
	struct s_zone		*prev;
	struct s_zone		*next;
}				t_zone;

typedef struct s_alloc
{
	t_zone		*tiny;
	t_zone		*small;
	t_block		*large;
}				t_alloc;

extern t_alloc g_alloc;
extern FILE *file;

int		init_alloc(void);
size_t	set_zone_size(unsigned int type);
void	*set_zone(unsigned int type);
void	*mymalloc(size_t size);
void	*ts_malloc(t_zone *zone, unsigned int type, size_t size);
void	*l_malloc(t_block *block, size_t size);
void	*mmap_call(size_t	size);
void	*search_free_block(t_zone *zone, unsigned int type, size_t size);
void	*create_lblock(t_block *block, size_t size);
void	*split_block(t_zone *zone, t_block *block, unsigned int type, size_t size);
void	*expand_zone(t_zone *zone, unsigned int type, size_t size);
void	myfree(void *ptr);
void	free_defrag(t_zone *zone, t_block *block);
void	munmap_zone(t_zone *zone);
void	munmap_block(t_block *block);
t_zone	*is_in_zone(t_zone	*zone, t_block *wanted);
int		search_block(t_block *head, t_block *wanted);
#endif
