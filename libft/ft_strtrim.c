/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 18:24:40 by dgameiro          #+#    #+#             */
/*   Updated: 2016/02/26 20:42:11 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int				i;
	int				len;
	char			*d;

	i = 0;
	len = ft_strlen(s);
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		len--;
	}
	if (len < 0)
		len = 0;
	if (!(d = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s = s + i;
	i = 0;
	while (i < len)
		d[i++] = *s++;
	d[i] = 0;
	return (d);
}
