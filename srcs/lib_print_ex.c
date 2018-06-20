/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_print_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:33:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/20 13:34:53 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void				print_content_ex(t_block *block)
{
	size_t	i;
	int		j;
	void	*ptr;

	i = 0;
	j = 0;
	ptr = (void*)(block + 1);
	while (i < block->size)
	{
		print_char_ex(((unsigned char*)ptr)[i], "0123456789abcdef");
		j++;
		if (j == 16 && i != block->size - 1)
		{
			ft_putchar('\n');
			j = 0;
		}
		else
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void				print_char_ex(unsigned long long c, char *hex)
{
	char	str[3];
	int		i;
	int		j;
	int		r;

	i = add_len(c);
	j = 0;
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
	ft_putstr(str);
}
