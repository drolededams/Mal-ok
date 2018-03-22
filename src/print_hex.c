/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:30:30 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/22 16:57:03 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem_hex(void)
{
	t_zone *tiny;
	t_zone *small;
	t_block *large;
	void *min;
	int *cur;
	unsigned long long line;

	tiny = T_HEAD;
	small = S_HEAD;
	large = L_HEAD;
	min = min_add(tiny, small, large);
	line = 0;
	if (!(cur = (int*)mymalloc(sizeof(int) * 1)))//init avec zero
		ft_putendl("malloc error");
	cur[0] = 0;
	while (min)
	{
		ft_putstr("0000000000000000 ");
		if (min == tiny)
		{
			line = ts_print_hex(tiny, cur, line);
			tiny = tiny->next;
		}
		else if (min == small)
		{
			line = ts_print_hex(small, cur, line);
			small = small->next;
		}
		else if (min == large)
		{
			line = l_print_hex(large, cur, line);
			large = large->next;
		}
		min = min_add(tiny, small, large);
	}
	myfree(cur);
}

unsigned long long ts_print_hex(t_zone *zone, int *cur, unsigned long long line)
{
	t_block *block;
	void *ptr;
	size_t i;

	block = zone->head;
	while(block && line < 49)
	{
		ptr = (void*)(block + 1);
		i = 0;
		while(i < 10)
		{
			print_char_hex(((char*)ptr)[i]);
			cur[0]++;
			if (cur[0] == 16)
			{
				cur[0] = 0;
				ft_putchar('\n');
				line += 16;;
				print_line_hex(line);
			}
			else
				ft_putchar(' ');
			i++;
		}
		block = block->next;
	}
	return (line);
}

unsigned long long l_print_hex(t_block *block, int *cur, unsigned long long line)
{
	void *ptr;
	size_t i;

	ptr = (void*)(block + 1);
	i = 0;
	while(i < block->size)
	{
		print_char_hex(((char*)ptr)[i]);
		cur[0]++;
		if (cur[0] == 16)
		{
			cur[0] = 0;
			ft_putchar('\n');
			line++;
			print_line_hex(line);
		}
		else
			ft_putchar('\n');
		i++;
	}
	return(line);
}

void print_line_hex(unsigned long long line)
{
	char *num;

	num = line_to_str(line, "0123456789abcdef");
	ft_putstr(num);
	ft_putchar(' ');
	myfree(num);
}

void print_char_hex(unsigned long long c)
{
	char *num;

	num = char_to_str(c, "0123456789abcdef");
	ft_putstr(num);
	myfree(num);
}

char *char_to_str(unsigned long long c, char *hex)
{
	char* str;
	int i;
	int j;
	int r;

	i = add_len(c);
	j = 0;
	if(!(str = (char*)mymalloc(sizeof(char) * (3))))
		fprintf(file, "Probleme allocation\n");
	str[2] = '\0';
	while (j < 2 - i)
	{
		str[j] = '0';
		j++;
	}
	while (c)
	{
		i--;
		r = c % 16;
		str[i] = hex[r];
		c /= 16;
	}
	return (str);
}

char *line_to_str(unsigned long long line, char *hex)
{
	char* str;
	int i;
	int j;
	int r;

	printf("line = %llu\n", line);
	i = add_len(line);
	printf("i = %d\n", i);
	j = 0;
	if(!(str = (char*)mymalloc(sizeof(char) * 17)))
		fprintf(file, "Probleme allocation\n");
	str[16] = '\0';
	printf("str line = %s\n", str);
	while (j < 16 - i)
	{
		str[j] = '0';
		j++;
	}
	printf("j = %d\n", j);
	printf("str line = %s\n", str);
	while (line)
	{
		i--;
		r = line % 16;
		str[i + j - 1] = hex[r];
		line /= 16;
	}
	printf("str line = %s\n", str);
	return (str);
}
