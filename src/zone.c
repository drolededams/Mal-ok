/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:53:00 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 18:55:50 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*search_free_block(t_zone *zone, unsigned int type, size_t size)
{
	t_zone *z_cur;
	t_block *b_cur;

	z_cur = zone;
	if (z_cur)
		b_cur = z_cur->head;
	while(z_cur)
	{
		while (b_cur)
		{
			if(b_cur->free && b_cur->size >= size)
				return (split_block(z_cur, b_cur, type, size));
			b_cur = b_cur->next;
		}
		z_cur = z_cur->next;
		if (z_cur)
			b_cur = z_cur->head;
	}
	return (NULL);
}

void	*create_lblock(t_block *block, size_t size)
{
	t_block *cur;
	t_block *new;

	cur = block;
	size = (((size + sizeof(t_block)) / getpagesize()) + 1) * getpagesize();
	if((new = mmap_call(size)) != NULL)
	{
		new->size = size - sizeof(t_block);
		new->free = 0;
		new->next = NULL;
		new->prev = NULL;
		if (cur)
		{
			while (cur->next)
				cur = cur->next;
			cur->next = new;
			new->prev = cur;
		}
		else
			cur = new;
		return ((void*)new + 1);
	}
	return (NULL);
}

void	*split_block(t_zone *zone, t_block *block, unsigned int type, size_t size)
{
	t_block		*new;
	size_t		resolution;
//get reso
	if (type == TINY)
		resolution = 16;
	else if (type == SMALL)
		resolution = T_MSIZE;
	else
		resolution = S_MSIZE;
	if (block->size > size + sizeof(t_block) + resolution)
	{
		new = (void*)block + sizeof(t_block) + size;
		new->free = 1;
		new->next = block->next;
		if (new->next)
			new->next->prev = new;
		else if (zone)
			zone->tail = new;
		new->size = block->size - size - sizeof(t_block);
		block->next = new;
		new->prev = block;
		block->size = size;
	}
	block->free = 0;
	if (block->next)
	{
		fprintf(file, "remaining size = %lu o\n\n", block->next->size);
	}
	else
		fprintf(file, "remaining size = 0 o\n\n");
	return((void*)(block + 1));
}

void	*expand_zone(t_zone *zone, unsigned int type, size_t size)
{
	t_zone *cur;
	t_zone *new;

	fprintf(file, "expand_zone\n");
	new = NULL;
	cur = zone;
	while (cur->next)
		cur = cur->next;
	fprintf(file, "last zone before exp = %p\n", (void*)(cur));
	if((new = set_zone(type)))
	{
		cur->next = new;
		new->prev = cur;
		return (split_block(new, new->head, type, size));
	}
	return (NULL);
}
