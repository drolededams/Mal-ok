/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:58:07 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 20:26:34 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	myfree(void *ptr)
{
	t_block *block;
	t_zone	*zone;

	if(!ptr)
		return ;
	fprintf(file, "\n\n!!!!!!!!!!!! FREE !!!!!!!!!!!\n\nfreeing ptr %p\n", ptr);
	block = (t_block*)ptr - 1;
	fprintf(file, "so freeing block %p\n", block);
	fprintf(file, "freeing block size %lu\n", block->size);
	if ((zone = is_in_zone(T_HEAD, block)))
	{
		block->free = 1;
		if((block->prev && block->prev->free) || (block->next && block->next->free))
			free_defrag(zone, block);
	}
	else if ((zone = is_in_zone(S_HEAD, block)))
	{
		block->free = 1;
		if((block->prev && block->prev->free) || (block->next && block->next->free))
			free_defrag(zone, block);
	}
	else if (search_block(L_HEAD, block))
		munmap_block(block);//set to free if can't unmap
}

void	free_defrag(t_zone *zone, t_block *block)
{
	t_block *prev;
	t_block *next;

	fprintf(file, "\n\n\n------defrag-------\n\n");
	fprintf(file, "block defraged = %p\n", block);
	fprintf(file, "block next defraged = %p\n", block->next);
	fprintf(file, "block prev defraged = %p\n", block->prev);
	prev = block->prev;
	next = block->next;
	if (prev && prev->free)
	{
		prev->size += block->size + sizeof(t_block);
		prev->next = next;
		next->prev = prev;
		//*(&block) = NULL;
		block = prev;
		fprintf(file, "\nfrag prev. bloc new add = %p\n", block);
		fprintf(file, "bloc new size = %lu\n", block->size);
		fprintf(file, "block next defraged = %p\n", block->next);
		fprintf(file, "block prev defraged = %p\n", block->prev);
	}
	next = block->next;
	if (next && next->free)
	{
		block->size += next->size + sizeof(t_block);
		block->next = next->next;
		if (next->next)
			next->next->prev = block;
		//*(&next) = NULL;
		fprintf(file, "\nfrag next. bloc new add (same = normal) = %p\n", block);
		fprintf(file, "frag next. bloc new size = %lu\n", block->size);
		fprintf(file, "block next defraged = %p\n", block->next);
		fprintf(file, "block prev defraged = %p\n", block->prev);
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

	fprintf(file, "\n---------\n\nunmapping zone = %p\n\n", zone);
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

	fprintf(file, "\n---------\n\nunmapping block = %p\n\n", block);
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
