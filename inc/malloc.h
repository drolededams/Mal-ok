/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:40:58 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/12 21:03:54 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define T_RSIZE 1048576
# define S_RSIZE 8388608
# define T_MSIZE 512
# define S_MSIZE 15360
# define T_MAX g_alloc->tmax
# define S_MAX g_alloc->smax
# define T_ZONE g_alloc->tiny
# define S_ZONE g_alloc->small
# define T_HEAD g_alloc->tiny->block
# define S_HEAD g_alloc->small->block
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
	size_t			size;
	t_block			*block;
	struct s_zone	*next;
}				t_zone;

typedef struct s_alloc
{
	size_t		tmax;
	size_t		smax;
	t_zone		*tiny;
	t_zone		*small;
	t_block		*large;
}				t_alloc;

int		init_zone(t_alloc *alloc);
int		init_bloc_zone(t_zone *zone, size_t max);
void	*mymalloc(size_t size);
#endif
