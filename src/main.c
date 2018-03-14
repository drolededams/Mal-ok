/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:56:10 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/14 18:03:01 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc g_alloc = {NULL, NULL, NULL};
FILE *file;
int num;

int main(void)
{
	char *str;
	char *str2;
	int i;

	num = 0;
	file = fopen("test", "w+");
	i = 0;
	fprintf (file, "t_zone size = %lu\n\n", sizeof(t_zone));
	while (i < 2048)
	{
		if(!(str = (char*)mymalloc(sizeof(char) * 488)))
			fprintf(file, "Probleme allocation\n");
		fprintf(file, "str 1 = %p\n\n############\n\n", str);
		i++;
	}
	if(!(str2 = (char*)mymalloc(sizeof(char) * 5)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 2 = %p\n", str2);
	return (0);
}

void	*mymalloc(size_t size)
{
	if (!size)
		return (NULL);
	if (!g_alloc.tiny)
		if (!init_alloc())
			return (NULL);
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

	if ((add = search_zone(zone, size)))
		return (add);
	else 
		return (expand_zone(zone, type, size));
}

void    *expand_zone(t_zone *zone, unsigned int type, size_t size)
{
	t_zone *cur;
	t_zone *new;

	fprintf(file, "expand_zone\n");
	new = NULL;
	cur = zone;
	while (cur->next)
		cur = cur->next;
	if((new = set_zone(type)))
	{
		cur->next = new;
		return (split_zone(new, size));
	}
	return (NULL);
}

void	*split_zone(t_zone *zone, size_t size)
{
	t_zone		*new;
	t_zone		*tmp;

	fprintf(file, "\n\n\n---------\n\n");
	if (zone->size == size)
	else if (zone->size < size + sizeof(t_zone) + 1)
	else
	new = (void*)zone + sizeof(t_zone) + size;
	new->free = 1;
	tmp = zone->next;
	new->next = tmp;
	new->num = zone->num;
	new->size = zone->size - size - sizeof(t_zone);
	zone->next = new;
	zone->size = size;
	zone->free = 0;
	fprintf(file, "return zone = %p\n", (void*)(zone + 1));
	fprintf(file, "number zone = %d\n", (zone->num));
	fprintf(file, "\nsize return= %luo\n", zone->size);
	fprintf(file, "\nremaining size = %luo\n", new->size);
	return((void*)(zone + 1));
}

void	*search_zone(t_zone *zone, size_t size)
{
	t_zone *cur;

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
	T_HEAD = set_zone(TINY);
	fprintf(file, "tiny + 1 zone = %p\n", (void*)(T_HEAD + 1));
	S_HEAD = set_zone(SMALL);
	fprintf(file, "small + 1 zone = %p\n", (void*)(S_HEAD + 1));
	L_HEAD = NULL;
	return(T_HEAD && S_HEAD);
}

void	*set_zone(unsigned int type)
{
	t_zone *zone;
	size_t size;

	size = set_zone_size(type);
	fprintf (file, "zone size = %lu\n\n", size);
	if((zone = mmap_call(size)) != NULL)
	{
		zone->size = size - sizeof(t_zone);
		zone->free = 1;
		zone->next = NULL;
		if (type == TINY)
		{
			zone->num = num++;
		}
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

	page_size = getpagesize();
	if (type == TINY)
	{
		q = T_RSIZE / page_size;
		r = (T_RSIZE % page_size) ? 1 : 0;
		size = (q + r) * page_size;
		while (size / (T_MSIZE + sizeof(t_zone)) < 100)
			size += page_size;
	}
	else
	{
		q = S_RSIZE / page_size;
		r = (S_RSIZE % page_size) ? 1 : 0;
		size = (q + r) * page_size;
		while (size / (S_MSIZE + sizeof(t_zone)) < 100)
			size += page_size;
	}
		return(size);
}

void	*mmap_call(size_t	size)
{
	void *add;

	if((add = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == ((void *) -1))
			return (NULL);
	return(add);
}
