/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 18:30:43 by dgameiro          #+#    #+#             */
/*   Updated: 2016/02/19 17:35:07 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t d;
	size_t s;

	d = ft_strlen(dest);
	s = ft_strlen(src);
	i = 0;
	while (i < s && i < n)
	{
		dest[d + i] = src[i];
		i++;
	}
	dest[d + i] = 0;
	return (dest);
}
