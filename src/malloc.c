/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:44:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 17:47:35 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
		return (l_malloc(L_HEAD, size));
}

void	*ts_malloc(t_zone *zone, unsigned int type, size_t size)
{
	void *ptr;

	if ((ptr = search_free_block(zone, type, size)))
		return (ptr);
	else 
		return (expand_zone(zone, type, size));
}

void	*l_malloc(t_block *block, size_t size)
{
	return (create_lblock(block, size));
}

void	*mmap_call(size_t	size)
{
	void *ptr;

	if((ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == ((void *) -1))
			return (NULL);
	return(ptr);
}
