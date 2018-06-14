/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_real.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:34:51 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/12 13:09:15 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

int		enough_space(t_block *block, size_t size)
{
	if (block->size + block->next->size + sizeof(t_block) >= size)
		return (1);
	return (0);
}

void	*fusion_block(t_zone *zone, int type, t_block *block, size_t size)
{
	t_block *fus;

	fus = block->next;
	block->size += fus->size + sizeof(t_block);
	block->next = fus->next;
	if (fus->next)
		fus->next->prev = block;
	else
		zone->tail = block;
	return (split_block(zone, block, type, size));
}

void	*ft_realloc_cpy(void *dst, const void *src, size_t n, size_t m)
{
	char *d;
	char *s;

	d = (char*)dst;
	s = (char*)src;
	if (d && s)
	{
		while (n && m)
		{
			*d = *s;
			d++;
			s++;
			n--;
			m--;
		}
	}
	return (dst);
}
