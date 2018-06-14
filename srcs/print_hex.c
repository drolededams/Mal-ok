/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:30:30 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/12 14:14:57 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void				show_alloc_mem_hex(void)
{
	t_zone				*tiny;
	t_zone				*small;
	t_block				*large;
	unsigned char		**str;

	tiny = T_HEAD;
	small = S_HEAD;
	large = L_HEAD;
	str = init_str_hex();
	print_hex_zone(tiny, small, large, str);
	free(str[0]);
	free(str[1]);
	free(str);
}

void				print_hex_zone(t_zone *tiny, t_zone *small, t_block *large,
		unsigned char **str)
{
	void				*min;
	unsigned long long	line;
	int					*cur;

	line = 0;
	if (!(cur = (int*)malloc(sizeof(int) * 2)))
		ft_putendl("malloc error");
	cur[0] = 0;
	cur[1] = 0;
	min = min_add(tiny, small, large);
	while (min)
	{
		if (min == tiny)
			line = ts_print_hex(&tiny, cur, line, str);
		else if (min == small)
			line = ts_print_hex(&small, cur, line, str);
		else if (min == large)
		{
			line = print_block_hex(large, cur, line, str);
			large = large->next;
		}
		min = min_add(tiny, small, large);
	}
	free(cur);
}

unsigned long long	ts_print_hex(t_zone **zone, int *cur,
		unsigned long long line, unsigned char **str)
{
	t_block	*block;

	block = (*zone)->head;
	while (block)
	{
		line = print_block_hex(block, cur, line, str);
		block = block->next;
	}
	*zone = (*zone)->next;
	return (line);
}

void				end_line(unsigned char **str, int *cur,
		unsigned long long line)
{
	if (same_str(str[0], str[1]))
	{
		if (!cur[1])
		{
			ft_putendl("*");
			cur[1] = 1;
		}
	}
	else
		print_all_hex(str, cur, line);
	str_cpy(str[0], str[1]);
	cur[0] = 0;
}

void				print_all_hex(unsigned char **str, int *cur,
		unsigned long long line)
{
	int j;

	print_line_hex(line);
	cur[1] = 0;
	j = 0;
	while (j < 15)
	{
		print_char_hex(str[1][j]);
		ft_putchar(' ');
		j++;
	}
	print_char_hex(str[1][j]);
	ft_putchar('\n');
}
