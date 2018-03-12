/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/31 11:08:37 by dgameiro          #+#    #+#             */
/*   Updated: 2016/03/14 15:14:23 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbr_to_int(char *nbr, char *base_from)
{
	int	j;
	int i;
	int	number;
	int	match;

	match = 0;
	number = 0;
	j = 0;
	i = 0;
	while (nbr[i] != 0)
	{
		while (match == 0)
		{
			if (nbr[i] == base_from[j])
			{
				match = 1;
				number = number * ft_strlen(base_from) + j;
			}
			j++;
		}
		i++;
		match = 0;
		j = 0;
	}
	return (number);
}

static char		*ft_int_to_final_base(int number, char *base_to)
{
	int		i;
	int		j;
	char	*final;

	final = (char*)malloc(sizeof(char) * 33);
	j = 0;
	if (number == 0)
	{
		final[j] = base_to[j];
		final[j + 1] = '\0';
		return (final);
	}
	while (number != 0)
	{
		i = number % ft_strlen(base_to);
		final[j] = base_to[i];
		number = number / ft_strlen(base_to);
		j++;
	}
	final[j] = '\0';
	return (final);
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	return (
	ft_strrev(ft_int_to_final_base(ft_nbr_to_int(nbr, base_from)
	, base_to)));
}
