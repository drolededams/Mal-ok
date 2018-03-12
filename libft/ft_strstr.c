/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 15:02:09 by dgameiro          #+#    #+#             */
/*   Updated: 2016/01/29 16:37:44 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	size;

	if (*s2 == '\0')
		return ((char *)s1);
	size = ft_strlen(s2);
	while (*s1)
	{
		if (ft_strncmp(s1, s2, size) == 0)
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
