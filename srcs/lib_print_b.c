/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_print_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:53:42 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/14 14:21:52 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void				ft_putsize_t(size_t n)
{
	if (n <= 9)
		ft_putchar(n + 48);
	else
	{
		ft_putsize_t(n / 10);
		ft_putsize_t(n % 10);
	}
}

void				ft_putull(unsigned long long n)
{
	if (n <= 9)
		ft_putchar(n + 48);
	else
	{
		ft_putsize_t(n / 10);
		ft_putsize_t(n % 10);
	}
}

void				print_add(void *add)
{
	char *num;

	num = add_to_str((unsigned long long)add, "0123456789ABCDEF");
	ft_putstr("0x");
	ft_putstr(num);
	free(num);
}
