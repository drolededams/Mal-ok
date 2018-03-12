/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:50:31 by dgameiro          #+#    #+#             */
/*   Updated: 2016/01/29 14:58:39 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	int len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if ((char)c == s[len])
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}
