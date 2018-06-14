/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:11:47 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/14 14:21:49 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_zone	*zone;
	void	*adr;

	adr = NULL;
	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_mutex);
	block = ((t_block*)ptr) - 1;
	if ((zone = is_in_zone(T_HEAD, block)))
		adr = t_realloc(ptr, size, zone, block);
	else if ((zone = is_in_zone(S_HEAD, block)))
		adr = s_realloc(ptr, size, zone, block);
	else if (search_block(L_HEAD, block))
		adr = l_realloc(ptr, size, block);
	pthread_mutex_unlock(&g_mutex);
	return (adr);
}

void	*t_realloc(void *ptr, size_t size, t_zone *zone, t_block *block)
{
	if (size <= block->size && size <= T_MSIZE)
		return (split_block(zone, block, TINY, size));
	if (size <= T_MSIZE)
		if (block->next && block->next->free && enough_space(block, size))
			return (fusion_block(zone, TINY, block, size));
	return (move_and_free(ptr, block->size, size));
}

void	*s_realloc(void *ptr, size_t size, t_zone *zone, t_block *block)
{
	if (T_MSIZE < size && size <= S_MSIZE)
	{
		if (size <= block->size)
			return (split_block(zone, block, SMALL, size));
		else if (block->next && block->next->free && enough_space(block, size))
			return (fusion_block(zone, SMALL, block, size));
	}
	return (move_and_free(ptr, block->size, size));
}

void	*l_realloc(void *ptr, size_t size, t_block *block)
{
	if (size <= block->size)
		return (ptr);
	else
		return (move_and_free(ptr, block->size, size));
}

void	*move_and_free(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	pthread_mutex_unlock(&g_mutex);
	new_ptr = malloc(new_size);
	pthread_mutex_lock(&g_mutex);
	new_ptr = ft_realloc_cpy(new_ptr, ptr, new_size, old_size);
	pthread_mutex_unlock(&g_mutex);
	free(ptr);
	pthread_mutex_lock(&g_mutex);
	return (new_ptr);
}
