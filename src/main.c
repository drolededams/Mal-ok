/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:56:10 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/13 18:31:44 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc g_alloc = {NULL, NULL, NULL};

int main(void)
{
	char *str;

	if(!(str = (char*)mymalloc(sizeof(char) * 6)))
		printf("Probleme allocation\n");
	str = "hello";
	printf("%s\n", str);
	printf("page size = %d\n", getpagesize());
	return (0);
}

void	*mymalloc(size_t size)
{
	if (!size)
		return (NULL);
	if (!g_alloc.tiny)
		if (!init_alloc())
			return (NULL);
	printf("zone 1 = %p\n", T_HEAD);
	printf("zone 2 = %p\n", S_HEAD);
	if (size <= T_MSIZE)
		return(ts_malloc(T_HEAD, TINY, size));
	else if (size <= S_MSIZE)
		return(ts_malloc(S_HEAD, SMALL, size));
	else
		return (NULL);
		//return (l_malloc(g_alloc->large));
}

void	*ts_malloc(t_zone *zone, unsigned int type, size_t size)
{
	t_zone *add;

	ft_putendl("ts_malloc");
	printf("zone = %p\n", zone);
	if ((add = search_zone(zone, size)))
		return (add);
	else 
		return (expand_zone(zone, type, size));
}

void    *expand_zone(t_zone *zone, unsigned int type, size_t size)
{
	t_zone *cur;
	t_zone *new;

	ft_putendl("expand_zone");
	new = NULL;
	cur = zone;
	while (cur->next)
		cur = cur->next;
	if((new =set_zone(type)))
	{
		cur->next = new;
		return (split_zone(new, size));
	}
	return (NULL);
}

void	*split_zone(t_zone *zone, size_t size)
{
	t_zone		*new;

	ft_putendl("split_zone");
	new = zone->next;
	new->free = 1;
	new->next = NULL;
	new->size = zone->size - size - sizeof(t_zone);
	zone->size = size;
	zone->free = 0;
	zone->next = new;
	return((void *) zone + 1);
}

void	*search_zone(t_zone *zone, size_t size)
{
	t_zone *cur;

	ft_putendl("search_zone");
	cur = zone;
	while(cur)
	{
		if(cur->free && cur->size >= size)
			return (split_zone(cur, size));
		cur = cur->next;
	}
	return (NULL);
}

int		init_alloc(void)
{
	ft_putendl("init_alloc");
	T_HEAD = set_zone(TINY);
	S_HEAD = set_zone(SMALL);
	L_HEAD = NULL;
	ft_putendl("init_alloc");
	return(T_HEAD && S_HEAD);
}

void	*set_zone(unsigned int type)
{
	t_zone *zone;
	size_t size;

	ft_putendl("set_zone");
	size = set_zone_size(type);
	if((zone = mmap_call(size)) != NULL)
	{
		zone->size = size - sizeof(t_zone);
		zone->free = 1;
		zone->next = NULL;
		return ((void*)zone);
	}
	return (NULL);
}

size_t		set_zone_size(unsigned int type)
{
	int				page_size;
	unsigned int	q;
	unsigned int	r;
	size_t			size;

	ft_putendl("set_zone_size");
	page_size = getpagesize();
	if (type == TINY)
	{
		q = T_RSIZE / page_size;
		r = (T_RSIZE % page_size) ? 1 : 0;
		size = (q + r) * page_size;
		while (size / T_MSIZE < 100)
			size += page_size;
	}
	else
	{
		q = S_RSIZE / page_size;
		r = (S_RSIZE % page_size) ? 1 : 0;
		size = (q + r) * page_size;
		while (size / S_MSIZE < 100)
			size += page_size;
	}
		return(size);
}

void	*mmap_call(size_t	size)
{
	void *add;

	ft_putendl("map");
	if((add = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == ((void *) -1))
			return (NULL);
	return(add);
}
