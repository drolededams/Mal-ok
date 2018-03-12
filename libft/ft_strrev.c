/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:08:55 by dgameiro          #+#    #+#             */
/*   Updated: 2016/03/14 15:15:16 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	trans;

	i = ft_strlen(str) - 1;
	j = 0;
	while (i > j)
	{
		trans = str[j];
		str[j] = str[i];
		str[i] = trans;
		i--;
		j++;
	}
	return (str);
}
