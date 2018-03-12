/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 19:21:27 by dgameiro          #+#    #+#             */
/*   Updated: 2016/02/28 13:08:02 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_alloc(int n)
{
	size_t alloc;

	alloc = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		alloc++;
	while (n)
	{
		n = n / 10;
		alloc++;
	}
	return (alloc);
}

char			*ft_itoa(int n)
{
	size_t	alloc;
	char	*num;
	long	nbr;

	nbr = (long)n;
	num = NULL;
	if (!(num = (char *)malloc(sizeof(char) * (ft_alloc(n) + 1))))
		return (NULL);
	alloc = ft_alloc(n);
	num[alloc] = 0;
	if (n == 0)
		num[0] = '0';
	if (n < 0)
	{
		num[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		num[--alloc] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (num);
}
