/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:11:47 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 18:55:48 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *myrealloc(void *ptr, size_t size)
{
	t_block *block;
	t_zone *zone;

	if (!ptr)
		return(mymalloc(size));
	if (!size)
	{
		myfree(ptr);
		return (NULL);
	}
	block = (t_block*)ptr - 1; //verif t_bloc size != t_zone size
	if ((zone = is_in_zone(T_HEAD, block)))
		return (t_realloc(ptr, size, zone, block));
	else if ((zone = is_in_zone(S_HEAD, block)))
		return (s_realloc(ptr, size, zone, block));
	else if (search_block(L_HEAD, block))
		return (l_realloc(ptr, size, block));
	return (NULL);
}

void	*t_realloc(void *ptr, size_t size, t_zone *zone, t_block *block)
{
	if (size <= block->size)
		return (split_block(zone, block, TINY, size));
	if (size <= T_MSIZE)
	{
		if (block->next && block->next->free)
			suitable_block(block, size);
	}
	return (move_free_ptr(ptr, block->size, size));
}

void	*s_realloc(void *ptr, size_t size, t_zone *zone, t_block *block)
{
	if (T_MSIZE < size && size <= S_MSIZE)
	{
		if (size <= block->size)
			return (split_block(zone, block, SMALL, size));
		else if (block->next && block->next->free)
			suitable_block(block, size);
	}
	return (move_free_ptr(ptr, block->size, size));
}

void	*l_realloc(void *ptr, size_t size, t_block *block)
{
	if (size <= block->size)
		return (ptr);
	else
		return (move_free_ptr(ptr, block->size, size));
}

void	*move_free_ptr(void *ptr, t_size old_size, t_size new_size)
{
	void *new_ptr;

	new_ptr = mymalloc(new_size);
	new_ptr = ft_realloc_cpy(new_ptr, ptr, new_size, old_size);
	free(ptr);
	return (new_ptr);
}

void	*ft_realloc_cpy(void *dst, const void *src, size_t n, size_t m)
{
	char *d;
	char *s;

	d = (char*)dst;
	s = (char*)src;
	if (d && s)
	{
		while (n && m)
		{
			*d = *s;
			d++;
			s++;
			n--;
			m--;
		}
	}
	return (dst);
}
