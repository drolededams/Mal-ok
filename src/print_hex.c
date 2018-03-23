/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:30:30 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/23 12:34:04 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			show_alloc_mem_hex(void)
{
	t_zone				*tiny;
	t_zone				*small;
	t_block				*large;
	int					*cur;
	unsigned char		**str;

	tiny = T_HEAD;
	small = S_HEAD;
	large = L_HEAD;
	str = init_str_hex();
	if (!(cur = (int*)mymalloc(sizeof(int) * 2)))//init avec zero
		ft_putendl("malloc error");
	cur[0] = 0;
	cur[1] = 0;
	print_hex_zone(tiny, small, large, min);
	myfree(cur);
	myfree(s_pre);
	myfree(s_cur);
}

char **init_str_hex(void)
{
	char **str;
	int i;

	if (!(str = (unsigned char**)mymalloc(sizeof(unsigned char*) * 2)))//init avec zero
		ft_putendl("calloc error");
	i = 0;
	while (i < 2)
	{
		if (!(str[i] = (unsigned char*)mycalloc(sizeof(unsigned char) * 17)))
			ft_putendl("calloc error");
		i++;
	}
	return (str);
}

void	print_hex_zone(t_zone *tiny, t_zone *small, t_block *large)
{
	void				*min;
	unsigned long long	line;

	line = 0;
	min = min_add(tiny, small, large);
	while (min)
	{
		if (min == tiny)
		{
			line = ts_print_hex(tiny, cur, line, s_pre, s_cur);
			tiny = tiny->next;
		}
		else if (min == small)
		{
			line = ts_print_hex(small, cur, line, s_pre, s_cur);
			small = small->next;
		}
		else if (min == large)
		{
			line = l_print_hex(large, cur, line, s_pre, s_cur);
			large = large->next;
		}
		min = min_add(tiny, small, large);
	}
}

unsigned long long	ts_print_hex(t_zone *zone, int *cur,
		unsigned long long line, unsigned char *s_pre, unsigned char *s_cur)
{
	t_block	*block;
	void	*ptr;
	size_t	i;
	size_t	j;

	block = zone->head;
	while (block)
	{
		ptr = (void*)(block + 1);
		i = 0;
		while (i < block->size)
		{
			s_cur[cur[0]] = ((unsigned char*)ptr)[i];
			cur[0]++;
			if (cur[0] == 16)
			{
				if (same_str(s_pre, s_cur))
				{
					if (!cur[1])
					{
						ft_putendl("*");
						cur[1] = 1;
					}
				}
				else
				{
					print_line_hex(line);
					cur[1] = 0;
					j = 0;
					while (j < 15)
					{
						print_char_hex(s_cur[j]);
						ft_putchar(' ');
						j++;
					}
					print_char_hex(s_cur[j]);
					ft_putchar('\n');
				}
				line += 16;
				str_cpy(s_pre, s_cur);
				cur[0] = 0;
			}
			i++;
		}
		block = block->next;
	}
	return (line);
}

int					same_str(unsigned char *pre, unsigned char *cur)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (pre[i] != cur[i])
			return (0);
		i++;
	}
	return (1);
}

void				str_cpy(unsigned char *pre, unsigned char *cur)
{
	int i;

	i = 0;
	while (i < 16)
	{
		pre[i] = cur[i];
		i++;
	}
}

unsigned long long	l_print_hex(t_block *block, int *cur, unsigned long long line, unsigned char *s_pre, unsigned char *s_cur)
{
	void	*ptr;
	size_t	i;
	size_t	j;

	ptr = (void*)(block + 1);
	i = 0;
	while (i < block->size)
	{
		s_cur[cur[0]] = ((unsigned char*)ptr)[i];
		cur[0]++;
		if (cur[0] == 16)
		{
			if (same_str(s_pre, s_cur))
			{
				if (!cur[1])
				{
					ft_putendl("*");
					cur[1] = 1;
				}
			}
			else
			{
				print_line_hex(line);
				cur[1] = 0;
				j = 0;
				while (j < 15)
				{
					print_char_hex(s_cur[j]);
					ft_putchar(' ');
					j++;
				}
				print_char_hex(s_cur[j]);
				ft_putchar('\n');
			}
			line += 16;
			str_cpy(s_pre, s_cur);
			cur[0] = 0;
		}
		i++;
	}
	return (line);
}

void				print_line_hex(unsigned long long line)
{
	char *num;

	num = line_to_str(line, "0123456789abcdef");
	ft_putstr(num);
	ft_putchar(' ');
	myfree(num);
}

void				print_char_hex(unsigned long long c)
{
	char *num;

	num = char_to_str(c, "0123456789abcdef");
	ft_putstr(num);
	myfree(num);
}

char				*char_to_str(unsigned long long c, char *hex)
{
	char	*str;
	int		i;
	int		j;
	int		r;

	i = add_len(c);
	j = 0;
	if (!(str = (char*)mymalloc(sizeof(char) * (3))))
		ft_putendl("Probleme allocation");
	str[2] = '\0';
	while (j < 2 - i)
	{
		str[j] = '0';
		j++;
	}
	while (c)
	{
		r = c % 16;
		str[i + j - 1] = hex[r];
		i--;
		c /= 16;
	}
	return (str);
}

char				*line_to_str(unsigned long long line, char *hex)
{
	char	*str;
	int		i;
	int		j;
	int		r;

	i = add_len(line);
	j = 0;
	if (!(str = (char*)mymalloc(sizeof(char) * 17)))
		fprintf(file, "Probleme allocation\n");
	str[16] = '\0';
	while (j < 16 - i)
	{
		str[j] = '0';
		j++;
	}
	while (line)
	{
		r = line % 16;
		str[i + j - 1] = hex[r];
		i--;
		line /= 16;
	}
	return (str);
}
