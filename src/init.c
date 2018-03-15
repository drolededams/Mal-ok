/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:55:42 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/15 19:58:40 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		init_alloc(void)
{
	T_HEAD = set_zone(TINY, 0);
	fprintf(file, "tiny + 1 zone = %p\n", (void*)(T_HEAD + 1));
	S_HEAD = set_zone(SMALL, 0);
	fprintf(file, "small + 1 zone = %p\n", (void*)(S_HEAD + 1));
	L_HEAD = NULL;
	return(T_HEAD && S_HEAD);
}

size_t		set_zone_size(unsigned int type)
{
	int				page_size;
	unsigned int	q;
	unsigned int	r;
	size_t			size;

	page_size = getpagesize();
	if (type == TINY)
	{
		q = T_RSIZE / page_size;
		r = (T_RSIZE % page_size) ? 1 : 0;
		size = (q + r) * page_size;
		while (size / (T_MSIZE + sizeof(t_zone)) < 100)
			size += page_size;
	}
	else
	{
		q = S_RSIZE / page_size;
		r = (S_RSIZE % page_size) ? 1 : 0;
		size = (q + r) * page_size;
		while (size / (S_MSIZE + sizeof(t_zone)) < 100)
			size += page_size;
	}
		return(size);
}

void	*set_zone(unsigned int type, unsigned int num)
{
	t_zone *zone;
	size_t size;

	size = set_zone_size(type);
	if((zone = mmap_call(size)) != NULL)
	{
		zone->size = size - sizeof(t_zone);
		zone->free = 1;
		zone->next = NULL;
		zone->prev = NULL;
		zone->num = num;
		return ((void*)zone);
	}
	return (NULL);
}
