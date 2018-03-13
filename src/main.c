/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:56:10 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/13 16:31:26 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc *g_alloc = NULL;

int main(void)
{
	printf("page size = %d\n", getpagesize());
	return (0);
}

void	*mymalloc(size_t size)
{
	if (!size)
		return (NULL);
	if (g_alloc == NULL)
		if (!init_zone())
			return (NULL);
	if (size <= T_MSIZE)
		return(ts_malloc(T_HEAD, size));
	else if (size <= S_MSIZE)
		return(ts_malloc(S_HEAD, size));
	else
		return (NULL);
		//return (l_malloc(g_alloc->large));
}

void	*ts_malloc(t_zone *zone, size_t size)
{
	t_zone *cur_zone;
	t_block *block;

	cur_zone = zone;
/*	if (zone->size + total > zone->max)
	{
		expand_zone(zone);
		cur_zone = cur_zone->next;
	}*/
	block = search_block(zone);
	if (block)
		return (block);
	else
	{
		cur_zone = expand_zone(zone);


	}

}

void	*split_block(t_block *block, size_t size)
{
	t_block		*new;

	block->next = new;
	new->free = 1;
	new->next = NULL;
	new->size = block->size - size - sizeof(t_block);
	block->size = size;
	block->free = 0;
	return((void *) block + 1);
}


t_zone		*space_available(t_zone *zone)
{
	t_zone *cur_zone;

}

t_block	*search_block(t_zone *zone, size_t size)
{
	t_zone *cur;

	cur = zone;
	while(cur)
	{
		while(cur->block)
		{
			if(cur->block->free && cur->block->size >= size)
				return (split_block(cur->block, size));
			cur->block = cur->block->next;
		}
		cur = cur->next;
	}
	return (NULL);
}

t_zone	*expand_zone(t_zone *zone)
{
	t_zone *cur;
	t_zone *new;

	new = NULL;
	cur = zone;
	while (cur->next)
		cur = cur->next;
	init_bloc_zone(new, zone->max);
	cur->next = new;
	return (new);
}

int		init_zone(void)
{
	set_zones_size();
	L_HEAD = NULL;
	return (init_bloc_zone(T_ZONE, T_MAX) && init_bloc_zone(S_ZONE, S_MAX));
}

void set_zones_size(void)
{
	int				page_size;
	unsigned int	q;
	unsigned int	r;

	page_size = getpagesize();
	q = T_RSIZE / page_size;
	r = (T_RSIZE % page_size) ? 1 : 0;
	T_MAX = (q + r) * page_size;
	while (T_MAX / T_MSIZE < 100)
		T_MAX += page_size;
	q = S_RSIZE / page_size;
	r = (S_RSIZE % page_size) ? 1 : 0;
	S_MAX = (q + r) * page_size;
	while (S_MAX / S_MSIZE < 100)
		S_MAX += page_size;
}

int		init_bloc_zone(t_zone *zone, size_t max)
{
	zone->size = 0;
	zone->next = NULL;
	zone->max = max;
	if((zone->block = mmap_call(max)) != NULL)
	{
		zone->block->size = max - sizeof(t_block);
		zone->block->free = 1;
		zone->block->next = NULL;
		return (1);
	}
	return (0);
}

void	*mmap_call(size_t	size)
{
	void *add;

	if((add = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == ((void *) -1))
			return (NULL);
	return(add);
}
