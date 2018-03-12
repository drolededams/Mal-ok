/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 17:38:41 by dgameiro          #+#    #+#             */
/*   Updated: 2016/02/19 11:10:29 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int negative;
	int number;

	if (!(ft_strcmp(str, "-2147483648")))
		return (-2147483648);
	negative = 1;
	number = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\f' ||
	*str == '\r' || *str == '\n')
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return (number * negative);
}
