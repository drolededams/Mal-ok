/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:40:13 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/23 11:54:03 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int					add_len(unsigned long long add)
{
	int length;

	length = 0;
	while (add)
	{
		add /= 16;
		length++;
	}
	return (length);
}

unsigned long long	ull_max(unsigned long long t, unsigned long long s,
		unsigned long long l)
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

void				print_total(unsigned long long total)
{
	ft_putstr("Total : ");
	ft_putull(total);
	if (total > 1)
		ft_putendl(" octets");
	else
		ft_putendl(" octet");
}

char				*add_to_str(unsigned long long add, char *hex)
{
	char	*str;
	int		i;
	int		r;

	i = add_len(add);
	if (!(str = (char*)mymalloc(sizeof(char) * (i + 1))))
		ft_putendl("Probleme allocation");
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

void				*min_add(void *tiny, void *small, void *large)
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
		return (large);
}
