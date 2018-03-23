/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_print_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:44:21 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/23 14:46:03 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

unsigned long long	print_block_hex(t_block *block, int *cur,
		unsigned long long line, unsigned char **str)
{
	void	*ptr;
	size_t	i;

	ptr = (void*)(block + 1);
	i = 0;
	while (i < block->size)
	{
		str[1][cur[0]] = ((unsigned char*)ptr)[i];
		cur[0]++;
		if (cur[0] == 16)
		{
			end_line(str, cur, line);
			line += 16;
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
