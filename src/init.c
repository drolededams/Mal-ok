/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:55:42 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 16:42:48 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		init_alloc(void)
{
	T_HEAD = set_zone(TINY);
	fprintf(file, "tiny zone = %p\n", (void*)(T_HEAD));
	fprintf(file, "tiny  1st block = %p\n", (void*)(T_HEAD + 1));
	fprintf(file, "tiny  1st alloc = %p\n\n", (void*)(T_HEAD + 2));
	S_HEAD = set_zone(SMALL);
	fprintf(file, "small zone = %p\n", (void*)(S_HEAD));
	fprintf(file, "small 1st block = %p\n", (void*)(S_HEAD + 1));
	fprintf(file, "small 1st alloc = %p\n\n", (void*)(S_HEAD + 2));
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
		while ((size - sizeof(t_zone)) / (T_MSIZE + sizeof(t_block)) < 100)
			size += page_size;
		fprintf(file, "TINY ZONE SIZE = %lu\n", size);
		fprintf(file, "TINY MAX MALLOC = %lu\n\n", (size - sizeof(t_zone)) / (T_MSIZE + sizeof(t_block)));
	}
	else
	{
		q = S_RSIZE / page_size;
		r = (S_RSIZE % page_size) ? 1 : 0;
		size = (q + r) * page_size;
		while ((size - sizeof(t_zone)) / (S_MSIZE + sizeof(t_block)) < 100)
			size += page_size;
		fprintf(file, "SMALL ZONE SIZE = %lu\n", size);
		fprintf(file, "SMALL MAX MALLOC = %lu\n\n", (size - sizeof(t_zone)) / (S_MSIZE + sizeof(t_block)));
	}
		return(size);
}

void	*set_zone(unsigned int type)
{
	t_zone *zone;
	size_t size;

	size = set_zone_size(type);
	if((zone = mmap_call(size)) != NULL)
	{
		fprintf(file, "zone = %p\n", (void*)(zone));
		zone->next = NULL;
		zone->prev = NULL;
		zone->head = (void*)(zone + 1);//verif zize t zone and t block
		zone->head->size = size - sizeof(t_zone) - sizeof(t_block);
		zone->head->free = 1;
		zone->head->next = NULL;
		zone->head->prev = NULL;
		zone->tail = zone->head;
		return ((void*)zone);
	}
	return (NULL);
}
