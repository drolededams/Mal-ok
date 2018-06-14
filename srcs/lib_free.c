/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:32:54 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/12 13:07:15 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_zone	*is_in_zone(t_zone *zone, t_block *wanted)
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
