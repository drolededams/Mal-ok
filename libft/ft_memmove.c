/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 15:14:23 by dgameiro          #+#    #+#             */
/*   Updated: 2016/03/12 17:40:45 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *d;
	char *s;

	d = (char*)dst;
	s = (char*)src;
	if (s < d)
	{
		s = s + len - 1;
		d = d + len - 1;
		while (len)
		{
			*d = *s;
			d--;
			s--;
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
