/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <dgameiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:27:40 by dgameiro          #+#    #+#             */
/*   Updated: 2016/02/27 12:03:14 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *tmp;

	if (!(tmp = (void*)malloc(sizeof(void) * size)))
		return (NULL);
	if (!(size))
		return (NULL);
	ft_bzero(tmp, size);
	return (tmp);
}
