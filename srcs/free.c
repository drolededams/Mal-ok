/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:58:07 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/20 16:14:33 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	free(void *ptr)
{
	t_block *block;
	t_zone	*zone;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	block = ((t_block*)ptr) - 1;
	if ((zone = is_in_zone(T_HEAD, block)))
	{
		block->free = 1;
		if ((block->prev && block->prev->free) ||
				(block->next && block->next->free))
			free_defrag(zone, block);
	}
	else if ((zone = is_in_zone(S_HEAD, block)))
	{
		block->free = 1;
		if ((block->prev && block->prev->free) ||
				(block->next && block->next->free))
			free_defrag(zone, block);
	}
	else if (search_block(L_HEAD, block))
		munmap_block(block);
	pthread_mutex_unlock(&g_mutex);
}

void	free_defrag(t_zone *zone, t_block *block)
{
	t_block *prev;
	t_block *next;

	prev = block->prev;
	if (prev && prev->free)
	{
		prev->size += block->size + sizeof(t_block);
		prev->next = block->next;
		block->next->prev = prev;
		block = prev;
	}
	next = block->next;
	if (next && next->free)
	{
		block->size += next->size + sizeof(t_block);
		block->next = next->next;
		if (next->next)
			next->next->prev = block;
	}
	if (!block->next)
		zone->tail = block;
	if (!block->prev)
		zone->head = block;
	if (zone->head == zone->tail && zone->prev)
		munmap_zone(zone);
}

void	munmap_zone(t_zone *zone)
{
	t_zone *prev;
	t_zone *next;

	prev = zone->prev;
	next = zone->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	munmap(zone, zone->head->size + sizeof(t_zone) + sizeof(t_block));
}

void	munmap_block(t_block *block)
{
	t_block *prev;
	t_block *next;

	prev = block->prev;
	next = block->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (L_HEAD == block)
		L_HEAD = next;
	munmap(block, block->size + sizeof(t_block));
	if (!prev && !next)
		L_HEAD = NULL;
}
