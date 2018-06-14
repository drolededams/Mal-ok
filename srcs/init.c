/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:55:42 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/12 13:08:00 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

int			init_alloc(void)
{
	T_HEAD = set_zone(TINY);
	S_HEAD = set_zone(SMALL);
	L_HEAD = NULL;
	return (T_HEAD && S_HEAD);
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
		while ((size - sizeof(t_zone)) / (T_MSIZE + sizeof(t_block)) < 100)
			size += page_size;
	}
	else
	{
		q = S_RSIZE / page_size;
		r = (S_RSIZE % page_size) ? 1 : 0;
		size = (q + r) * page_size;
		while ((size - sizeof(t_zone)) / (S_MSIZE + sizeof(t_block)) < 100)
			size += page_size;
	}
	return (size);
}

void		*set_zone(unsigned int type)
{
	t_zone *zone;
	size_t size;

	size = set_zone_size(type);
	if ((zone = mmap_call(size)) != NULL)
	{
		zone->next = NULL;
		zone->prev = NULL;
		zone->head = (void*)(zone + 1);
		zone->head->size = size - sizeof(t_zone) - sizeof(t_block);
		zone->head->free = 1;
		zone->head->next = NULL;
		zone->head->prev = NULL;
		zone->tail = zone->head;
		return ((void*)zone);
	}
	return (NULL);
}
