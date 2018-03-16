/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:56:10 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/16 15:04:48 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "malloc.h"

t_alloc g_alloc;
FILE *file;

int main(void)
{
	char *str;
	char *str2;
	char *str3;
	int i;
	size_t a;
	size_t b;
	size_t c;

	file = fopen("test", "w+");
	g_alloc.tiny = NULL;
	g_alloc.small = NULL;
	g_alloc.large = NULL;
	i = 0;

	fprintf (file, "t_zone size = %lu\n\n", sizeof(t_zone));
	fprintf (file, "t_block size = %lu\n\n", sizeof(t_block));

	/*TINY ZONE*/
	while (i < 1927)
	{
		if(!(str = (char*)mymalloc(sizeof(char) * 512)))
			fprintf(file, "Probleme allocation\n");
		fprintf(file, "str 1 = %p\n\n############\n\n", str);
		i++;
	}

	fprintf(file,"LAST TINY in zone ??\n\n");
	if(!(str = (char*)mymalloc(sizeof(char) * 214)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 1 = %p\n\n############\n\n", str);

	fprintf(file,"NEW TINY zone MAP??\n\n");
	if(!(str = (char*)mymalloc(sizeof(char) * 17)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 1 = %p\n\n############\n\n", str);

	//Test free and unmamping
	if(!(str3 = (char*)mymalloc(sizeof(char) * 224)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 3 = %p\n\n############\n\n", str3);
	b = (size_t)(str3);
	fprintf(file, "first b str 3 = %lu\n", b);
	myfree(str);
	myfree(str3);

	if(!(str2 = (char*)mymalloc(sizeof(char) * 1024)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 2 = %p\n\n############\n\n", str2);
	a = (size_t)(str2);
	str2[0] = '2';
	str2[1] = '\0';
	ft_putendl(str2);
	if(!(str3 = (char*)mymalloc(sizeof(char) * 83)))
		fprintf(file, "Probleme allocation\n");
	b = (size_t)(str3);
	c = (size_t)(str3 + 81);
	ft_putendl(str2);
	str3[81] = '3';
	ft_putendl(str2);
	fprintf(file, "str 3 = %p\n", str3);
	fprintf(file, "str 3 = %lu\n", (size_t)str3);
	fprintf(file, "str 3 = %p\n", str3 + 81);
	fprintf(file, "a str 2 = %lu\n", a);
	fprintf(file, "b str 3 = %lu\n", b);
	fprintf(file, "end c str 3 = %lu\n", c);
	fprintf(file, "a - b = %lu\n", a - b);
	fprintf(file, "a - c = %lu\n", a - c);
	fprintf(file, "b - a = %lu\n", b - a);
	fprintf(file, "c - a = %lu\n", c - a);
	return (0);
}
