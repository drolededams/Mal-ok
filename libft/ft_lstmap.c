/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 17:11:04 by dgameiro          #+#    #+#             */
/*   Updated: 2016/03/14 12:37:47 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *updated;
	t_list *new;

	if (!lst)
		return (NULL);
	if (!(updated = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	updated = f(lst);
	new = updated;
	while (lst->next)
	{
		if (!(updated->next = (t_list*)malloc(sizeof(t_list))))
			return (NULL);
		updated->next = f(lst->next);
		updated = updated->next;
		lst = lst->next;
	}
	updated = NULL;
	return (new);
}
