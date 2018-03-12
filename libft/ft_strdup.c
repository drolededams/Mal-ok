/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 18:44:13 by dgameiro          #+#    #+#             */
/*   Updated: 2016/01/22 17:09:18 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*s2;
	unsigned int	len;

	len = ft_strlen(s1);
	if (!(s2 = (char*)malloc(sizeof(*s2) * (len + 1))) || !s1)
		return (NULL);
	return (ft_strcpy(s2, s1));
}
