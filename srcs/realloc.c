/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:11:47 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/23 16:30:56 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*myrealloc(void *ptr, size_t size)
{
	t_block	*block;
	t_zone	*zone;

	if (!ptr)
		return (mymalloc(size));
	if (!size)
	{
		myfree(ptr);
		return (NULL);
	}
	block = ((t_block*)ptr) - 1;
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
		if (block->next && block->next->free && enough_space(block, size))
			return (fusion_block(zone, TINY, block, size));
	return (move_and_free(ptr, block->size, size));
}

void	*s_realloc(void *ptr, size_t size, t_zone *zone, t_block *block)
{
	if (T_MSIZE < size && size <= S_MSIZE)
	{
		if (size <= block->size)
			return (split_block(zone, block, SMALL, size));
		else if (block->next && block->next->free && enough_space(block, size))
			return (fusion_block(zone, SMALL, block, size));
	}
	return (move_and_free(ptr, block->size, size));
}

void	*l_realloc(void *ptr, size_t size, t_block *block)
{
	if (size <= block->size)
		return (ptr);
	else
		return (move_and_free(ptr, block->size, size));
}

void	*move_and_free(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	new_ptr = mymalloc(new_size);
	new_ptr = ft_realloc_cpy(new_ptr, ptr, new_size, old_size);
	myfree(ptr);
	return (new_ptr);
}
