/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:14:19 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/23 12:31:28 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				show_alloc_mem(void)
{
	t_zone				*tiny;
	t_zone				*small;
	t_block				*large;
	void				*min;
	unsigned long long	total;

	tiny = T_HEAD;
	small = S_HEAD;
	large = L_HEAD;
	min = min_add(tiny, small, large);
	total = print_zone(tiny, small, large, min);
	print_total(total);
}

unsigned long long	print_zone(t_zone *tiny, t_zone *small, t_block *large,
		void *min)
{
	unsigned long long total;

	total = 0;
	while (min)
	{
		if (min == tiny)
		{
			total += ts_print(tiny, TINY);
			tiny = tiny->next;
		}
		else if (min == small)
		{
			total += ts_print(small, SMALL);
			small = small->next;
		}
		else if (min == large)
		{
			total += l_print(large);
			large = large->next;
		}
		min = min_add(tiny, small, large);
	}
	return (total);
}

size_t				ts_print(t_zone *zone, int type)
{
	t_block	*block;
	size_t	block_size;

	block_size = 0;
	block = zone->head;
	if (type == TINY)
		ft_putstr("TINY : ");
	else
		ft_putstr("SMALL : ");
	print_add((void*)zone);
	ft_putchar('\n');
	while (block)
	{
		if (block->free == 0)
			block_size += print_block(block);
		block = block->next;
	}
	return (block_size);
}

size_t				l_print(t_block *block)
{
	ft_putstr("LARGE : ");
	print_add((void*)block);
	ft_putchar('\n');
	return (print_block(block));
}

size_t				print_block(t_block *block)
{
	print_add((void*)(block + 1));
	ft_putstr(" - ");
	print_add((void*)(block + 1) + block->size);
	ft_putstr(" : ");
	ft_putsize_t(block->size);
	if (block->size > 1)
		ft_putendl(" octets");
	else
		ft_putendl(" octet");
	return (block->size);
}
