/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:58:07 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 13:46:59 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	myfree(void *ptr)
{
	t_block *block;
	t_zone	*zone;

	if(!ptr)
		return ;
	fprintf(file, "freeing %p\n", ptr);
	block = (t_block*)ptr - 1;
	if ((zone = is_in_zone(T_HEAD, block)))
	{
		if((block->prev && block->prev->free) || (block->next && block->next->free))
			free_defrag(zone, block);
	}
	else if ((zone = is_in_zone(S_HEAD, block)))
	{
		if((block->prev && block->prev->free) || (block->next && block->next->free))
			free_defrag(zone, block);
	}
	else if (search_block(L_HEAD, block))
		munmap_block(block);
}

void	free_defrag(t_zone *zone, t_block *block)
{
	t_block *prev;
	t_block *next;

	prev = block->prev;
	next = block->next;
	if (prev && prev->free)
	{
		prev->size += block->size + sizeof(t_block);
		prev->next = next;
		next->prev = prev;
		//*(&block) = NULL;
		block = prev;
	}
	next = block->next;
	if (next && next->free)
	{
		block->size += next->size + sizeof(t_block);
		block->next = next->next;
		if (next->next)
			next->next->prev = block;
		//*(&next) = NULL;
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
	prev->next = next;
	if (next)
		next->prev = prev;
	if((zone->head->size + sizeof(t_block) + sizeof(t_zone)) % getpagesize() == 0)
		fprintf(file, "modulo munmap zone OK\n\n");
	else
		fprintf(file, "modulo munmap zone KOOOO\n\n");
	if (munmap(zone, zone->head->size + sizeof(t_zone) + sizeof(t_block)) == 0)
		fprintf(file, "munmap zone OK\n\n");
	else
		fprintf(file, "munmap zone KOOOOO\n\n");
}

void	munmap_block(t_block *block)
{
	t_block *prev;
	t_block *next;

	prev = block->prev;
	next = block->next;
	prev->next = next;
	if (next)
		next->prev = prev;
	if ((block->size + sizeof(t_block)) % getpagesize() == 0)
		fprintf(file, "modulo munmap block OK\n\n");
	else
		fprintf(file, "modulo munmap block KOOOO\n\n");
	if (munmap(block, block->size + sizeof(t_block)) == 0)
		fprintf(file, "munmap block OK\n\n");
	else
		fprintf(file, "munmap block KOOOOO\n\n");
}

t_zone	*is_in_zone(t_zone	*zone, t_block *wanted)
{
	t_zone	*z_cur;

	z_cur = zone;
	while (z_cur)
	{
		if (z_cur->head <= wanted && wanted <= z_cur->tail)
		{	
			if (search_block(z_cur->head, wanted))
				return (z_cur);
			else
				return (NULL);
		}
		z_cur = z_cur->next;
	}
	return (NULL);
}

int		search_block(t_block *head, t_block *wanted)
{
	t_block *block;

	block = head;
	while (block)
	{
		if (block == wanted)
		{
			block->free = 1;
			return (1);
		}
		block = block->next;
	}
	return (0);
}
