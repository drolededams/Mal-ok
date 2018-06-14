/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:44:52 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/14 12:38:32 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_alloc g_alloc = {NULL, NULL, NULL};
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	void *ptr;

	if (!size)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	if (!g_alloc.tiny)
		if (!init_alloc())
		{
			pthread_mutex_unlock(&g_mutex);
			return (NULL);
		}
	if (size <= T_MSIZE)
		ptr = ts_malloc(T_HEAD, TINY, size);
	else if (size <= S_MSIZE)
		ptr = ts_malloc(S_HEAD, SMALL, size);
	else
		ptr = l_malloc(L_HEAD, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
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

void	*mmap_call(size_t size)
{
	void *ptr;

	if ((ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1,
					0)) == MAP_FAILED)
		return (NULL);
	return (ptr);
}
