/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:53:00 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/15 20:00:07 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*search_zone(t_zone *zone, unsigned int type, size_t size)
{
	t_zone *cur;

	cur = zone;
	while(cur)
	{
		if(cur->free && cur->size >= size)
			return (split_zone(cur, type, size));
		cur = cur->next;
	}
	return (NULL);
}

void	*create_lzone(t_zone *zone, size_t size)
{
	t_zone *cur;
	t_zone *new;

	cur = zone;
	if((new = mmap_call(size + sizeof(t_zone))) != NULL)
	{
		new->size = size;
		new->free = 0;
		new->next = NULL;
		new->prev = NULL;
		new->num = 0;
		if (cur)
		{
			while (cur->next)
				cur = cur->next;
			cur->next = new;
			new->prev = cur;
			new->num = cur->num + 1;
		}
		else
			cur = new;
		return ((void*)new + 1);
	}
	return (NULL);
}

void	*split_zone(t_zone *zone, unsigned int type, size_t size)
{
	t_zone		*new;
	size_t		resolution;
//get reso
	if (type == TINY)
		resolution = 16;
	else if (type == SMALL)
		resolution = T_MSIZE;
	else
		resolution = S_MSIZE;
	if (zone->size > size + sizeof(t_zone) + resolution)
	{
		new = (void*)zone + sizeof(t_zone) + size;
		new->free = 1;
		new->num = zone->num;
		new->next = zone->next;
		if(new->next)
			new->next->prev = new;
		new->size = zone->size - size - sizeof(t_zone);
		zone->next = new;
		new->prev = zone;
		zone->size = size;
	}
	zone->free = 0;
	return((void*)(zone + 1));
}
