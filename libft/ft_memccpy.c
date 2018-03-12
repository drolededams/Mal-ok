/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 19:41:43 by dgameiro          #+#    #+#             */
/*   Updated: 2016/02/05 12:23:04 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const char	*s1;
	char		*s2;

	s1 = (const char*)src;
	s2 = (char*)dst;
	while (n)
	{
		*s2 = *s1;
		s2++;
		if (*s1 == (char)c)
			return (s2);
		s1++;
		n--;
	}
	return (NULL);
}
