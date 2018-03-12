/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:01:58 by dgameiro          #+#    #+#             */
/*   Updated: 2016/03/12 15:11:50 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*st;

	st = (const char*)s;
	while (n)
	{
		if (*st == (const char)c)
			return ((void*)st);
		n--;
		st++;
	}
	return (NULL);
}
