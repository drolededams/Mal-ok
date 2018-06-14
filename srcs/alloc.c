/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 09:43:06 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/12 18:29:54 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(nmemb * size);
	if (ptr)
	{
		i = 0;
		while (i < nmemb * size)
		{
			((unsigned char*)ptr)[i] = 0;
			i++;
		}
	}
	return (ptr);
}

void	*reallocf(void *ptr, size_t size)
{
	void *new_ptr;

	new_ptr = realloc(ptr, size);
	if (!new_ptr)
		free(ptr);
	return (new_ptr);
}

void	*reallocarray(void *ptr, size_t n, size_t size)
{
	if ((n > OVERFLOW_X || size > OVERFLOW_X) &&
			(size > 0 && SIZE_MAX / size < n))
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (realloc(ptr, n * size));
}
