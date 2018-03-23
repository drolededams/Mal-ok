/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 09:43:06 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/23 19:01:44 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*mycalloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = mymalloc(nmemb * size);
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

void	*myreallocf(void *ptr, size_t size)
{
	void *new_ptr;

	new_ptr = myrealloc(ptr, size);
	if (!new_ptr)
		myfree(ptr);
	return (new_ptr);
}

void	*myreallocarray(void *ptr, size_t n, size_t size)
{
	if ((n > OVERFLOW_X || size > OVERFLOW_X) &&
			(size > 0 && SIZE_MAX / size < n))
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (myrealloc(ptr, n * size));
}
