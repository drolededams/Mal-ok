/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:56:10 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/12 21:03:50 by dgameiro         ###   ########.fr       */
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
		return(ts_malloc(T_HEAD, T_MAX, size));
	else if (size <= S_MSIZE)
		return(ts_malloc(S_HEAD, S_MAX, size));
	else
		return (l_malloc(g_alloc->large));
}

void	*ts_malloc(t_zone *zone, size_t max, size_t size)
{
	t_size total;

	total = size + sizeof(t_block);
	if (zone->size + total > max)
		expand_zone(zone, max);
}

void	expand_zone(t_zone *zone)
{
	t_zone *cur;
	t_zone *new;

	curr = zone;
	while (curr->next)
		curr = curr->next;
	init_bloc_zone(new);
	curr->next = new;
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
	q = (T_RSIZE / page_size) ? T_RSIZE / page_size : 0;
	r = (T_RSIZE % page_size) ? 1 : 0;
	T_MAX = (q + r) * page_size;
	while (T_MAX / T_MSIZE < 100)
		T_MAX += page_size;
	q = (S_RSIZE / page_size) ? S_RSIZE / page_size : 0;
	r = (S_RSIZE % page_size) ? 1 : 0;
	S_MAX = (q + r) * page_size;
	while (S_MAX / S_MSIZE < 100)
		S_MAX += page_size;
}

int		init_bloc_zone(t_zone *zone, size_t max)
{
	zone->size = 0;
	zone-next = NULL;
	if((zone->block = mmap_call(max)) != NULL)
		return (1);
	return (0);
}

void	*mmap_call(t_size	size)
{
	void *add;

	if((add = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == ((void *) -1))
			return (NULL);
	return(add);
}
