/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:40:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 10:10:55 by dgameiro         ###   ########.fr       */
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

typedef struct	s_zone
{
	size_t		size;
	int			free;
	unsigned int	num;
	struct s_zone *next;
	struct s_zone *prev;
}				t_zone;

typedef struct s_alloc
{
	t_zone		*tiny;
	t_zone		*small;
	t_zone		*large;
}				t_alloc;

extern t_alloc g_alloc;
extern FILE *file;

void	*mymalloc(size_t size);
void	myfree(void *ptr);
void	*ts_malloc(t_zone *zone, unsigned int type, size_t size);
void	*l_malloc(t_zone *zone, unsigned int type, size_t size);
void    *expand_zone(t_zone *zone, unsigned int type, size_t size);
void	*search_zone(t_zone *zone, unsigned int type, size_t size);
void	*split_zone(t_zone *zone, unsigned int type, size_t size);
int		init_alloc(void);
void	*set_zone(unsigned int type, unsigned int num);
void	*create_lzone(t_zone *zone, size_t size);
size_t		set_zone_size(unsigned int type);
void	*mmap_call(size_t	size);
void	free_defrag(t_zone *zone);
#endif
