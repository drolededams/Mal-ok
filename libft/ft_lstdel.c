/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:25:09 by dgameiro          #+#    #+#             */
/*   Updated: 2016/03/14 12:36:59 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *to_free;

	tmp = *alst;
	while (tmp)
	{
		del(tmp->content, tmp->content_size);
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	*alst = NULL;
}
