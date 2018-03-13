/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:40:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/13 16:31:22 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define T_RSIZE 1048576
# define S_RSIZE 8388608
# define T_MSIZE 512 + sizeof(t_block)
# define S_MSIZE 15360 + sizeof(t_block)
# define T_MAX g_alloc->tiny->max
# define S_MAX g_alloc->small->max
# define T_ZONE g_alloc->tiny
# define S_ZONE g_alloc->small
# define T_HEAD g_alloc->tiny
# define S_HEAD g_alloc->small
# define L_HEAD g_alloc->large
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
}				t_block;

typedef struct s_zone
{
	size_t			max;
	t_block			*block;
	struct s_zone	*next;
}				t_zone;

typedef struct s_alloc
{
	t_block		*tiny;
	t_block		*small;
	t_block		*large;
}				t_alloc;

void	*mymalloc(size_t size);
void	*ts_malloc(t_zone *zone, size_t size);
void	expand_zone(t_zone *zone);
int		init_zone(void);
void set_zones_size(void);
int		init_bloc_zone(t_zone *zone, size_t max);
void	*mmap_call(size_t	size);
#endif
