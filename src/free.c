/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:58:07 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 10:00:55 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	myfree(void *ptr)
{
	t_zone *zone;
	if(!ptr)
		return ;
	fprintf(file, "freeing %p\n", ptr);
	zone = (t_zone*)ptr - 1;
	zone->free = 1;
	if((zone->prev && zone->prev->free) || (zone->next && zone->next->free))
		free_defrag(zone);
}

void	free_defrag(t_zone *zone)
{
	t_zone *prev;
	t_zone *next;

	prev = zone->prev;
	next = zone->next;
	if (prev && prev->free)
	{
		prev->size += zone->size + sizeof(t_zone);
		prev->next = next;
		next->prev = prev;
		zone = prev;
	}
	next = zone->next;
	if (next && next->free)
	{
		zone->size += next->size + sizeof(t_zone);
		zone->next = next->next;
		if (next->next)
			next->next->prev = zone;
	}
}
