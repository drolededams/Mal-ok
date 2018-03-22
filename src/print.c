/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:14:19 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/22 14:15:16 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void show_alloc_mem(void)
{
	t_zone *tiny;
	t_zone *small;
	t_block *large;
	void *min;
	unsigned long long total;

	tiny = T_HEAD;
	small = S_HEAD;
	large = L_HEAD;
	min = min_add(tiny, small, large);
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
	ft_putstr("Total : ");
	ft_putull(total);
	if (total > 1)
		ft_putendl(" octets");
	else
		ft_putendl(" octet");

}

size_t	ts_print(t_zone *zone, int type)
{
	t_block *block;
	size_t block_size;

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

size_t	l_print(t_block *block)
{
	ft_putstr("LARGE : ");
	print_add((void*)block);
	ft_putchar('\n');
	return(print_block(block));
}

size_t print_block(t_block *block)
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

void	ft_putsize_t(size_t n)
{
	if (n <= 9)
		ft_putchar(n + 48);
	else
	{
		ft_putsize_t(n / 10);
		ft_putsize_t(n % 10);
	}
}

void	ft_putull(unsigned long long n)
{
	if (n <= 9)
		ft_putchar(n + 48);
	else
	{
		ft_putsize_t(n / 10);
		ft_putsize_t(n % 10);
	}
}

void print_add(void *add)
{
	char *num;

	num = add_to_str((unsigned long long)add, "0123456789ABCDEF");
	ft_putstr("0x");
	ft_putstr(num);
	myfree(num);
}

void *min_add(void *tiny, void *small, void *large)
{
	unsigned long long t;
	unsigned long long s;
	unsigned long long l;
	unsigned long long max;

	t = (unsigned long long)tiny;
	s = (unsigned long long)small;
	l = (unsigned long long)large;
	max = ull_max(t, s, l);
	if (max == 0)
		return (NULL);
	if (tiny == NULL)
		t = max + 1;
	if (small == NULL)
		s = max + 1;
	if (large == NULL)
		l = max + 1;
	if (t < s && t < l)
		return (tiny);
	if (s < t && s < l)
		return (small);
	else
		return(large);
}

unsigned long long ull_max(unsigned long long t, unsigned long long s, unsigned long long l)
{
	if (t == s && l == s && l == 0)
		return (0);
	else if (l > s && l > t)
		return (l);
	else if (s > l && s > t)
		return (s);
	else
		return (t);
}


char *add_to_str(unsigned long long add, char *hex)
{
	char* str;
	int i;
	int r;

	i = add_len(add);
	if(!(str = (char*)mymalloc(sizeof(char) * (i + 1))))
		fprintf(file, "Probleme allocation\n");
	str[i] = '\0';
	while (add)
	{
		i--;
		r = add % 16;
		str[i] = hex[r];
		add /= 16;
	}
	return (str);
}

int add_len(unsigned long long add)
{
	int length;

	length = 0;
	while(add)
	{
		add /= 16;
		length++;
	}
	return (length);
}
