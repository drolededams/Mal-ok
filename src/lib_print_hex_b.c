/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_print_hex_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:47:18 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/23 14:48:24 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

unsigned char		**init_str_hex(void)
{
	unsigned char	**str;
	int				i;

	if (!(str = (unsigned char**)mymalloc(sizeof(unsigned char*) * 2)))
		ft_putendl("malloc error");
	i = 0;
	while (i < 2)
	{
		if (!(str[i] = (unsigned char*)mycalloc(17, sizeof(unsigned char))))
			ft_putendl("calloc error");
		i++;
	}
	return (str);
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
