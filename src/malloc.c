/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:44:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 10:05:09 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc g_alloc = {NULL, NULL, NULL};

void	*mymalloc(size_t size)
{
	if (!size)
		return (NULL);
	if (!g_alloc.tiny)
		if (!init_alloc())
			return (NULL);
	if (size <= T_MSIZE)
		return(ts_malloc(T_HEAD, TINY, size));
	else if (size <= S_MSIZE)
		return(ts_malloc(S_HEAD, SMALL, size));
	else
		return (l_malloc(T_HEAD, LARGE, size));
}

void	*ts_malloc(t_zone *zone, unsigned int type, size_t size)
{
	t_zone *add;

	if ((add = search_zone(zone, type, size)))
		return (add);
	else 
		return (expand_zone(zone, type, size));
}

void	*l_malloc(t_zone *zone, unsigned int type, size_t size)
{
	t_zone *add;

	if((add = search_zone(zone, type, size)))
		return(add);
	else
		return (create_lzone(zone, size));
}

void	*mmap_call(size_t	size)
{
	void *add;

	if((add = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == ((void *) -1))
			return (NULL);
	return(add);
}
