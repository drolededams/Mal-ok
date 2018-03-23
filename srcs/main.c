/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:56:10 by dgameiro          #+#    #+#             */
/*   Updated: 2018/03/23 10:29:21 by dgameiro         ###   ########.fr       */
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
	char *to_free_1;
	char *to_free_2;
	char *to_free_3;
	int i;
	int j;
	size_t a;
	size_t b;
	size_t c;

	//show_alloc_mem();
	file = fopen("test", "w+");
	g_alloc.tiny = NULL;
	g_alloc.small = NULL;
	g_alloc.large = NULL;
	i = 0;

	fprintf (file, "t_zone size = %lu\n\n", sizeof(t_zone));
	fprintf (file, "t_block size = %lu\n\n", sizeof(t_block));
	fprintf (file, "size_t size = %lu\n\n", sizeof(size_t));

	if(!(to_free_1 = (char*)mymalloc(sizeof(char) * 16)))
		fprintf(file, "Probleme allocation\n");
	if(!(to_free_2 = (char*)mymalloc(sizeof(char) * 16)))
		fprintf(file, "Probleme allocation\n");
	if(!(to_free_3 = (char*)mymalloc(sizeof(char) * 16)))
		fprintf(file, "Probleme allocation\n");
	/*if(!(to_free_1 = (char*)mymalloc(sizeof(char) * 256)))
		fprintf(file, "Probleme allocation\n");
	if(!(to_free_2 = (char*)mymalloc(sizeof(char) * 612)))
		fprintf(file, "Probleme allocation\n");
	if(!(to_free_3 = (char*)mymalloc(sizeof(char) * 455480)))
		fprintf(file, "Probleme allocation\n");
*/
	while (i < 16)
	{
		to_free_1[i] = 65 + i;
		to_free_2[i] = to_free_1[i];
		to_free_3[i] = to_free_1[i];
		i++;
	}
	i = 0;
	if(!(to_free_2 = (char*)mymalloc(sizeof(char) * 16)))
		fprintf(file, "Probleme allocation\n");
	while (i < 16)
	{
		to_free_1[i] = 65 + i;
		to_free_2[i] = to_free_1[i];
		to_free_3[i] = to_free_1[i];
		i++;
	}
	i = 0;
	j = 0;
	if(!(to_free_2 = (char*)mymalloc(sizeof(char) * 1000000)))
		fprintf(file, "Probleme allocation\n");
	while(i < 1000000)
	{
		if (j == 16)
			j = 0;
		to_free_2[i] = 'A' + j;
		i++;
		j++;
	}
	show_alloc_mem_hex();
	//show_alloc_mem();
	i = 0;

	if(!(to_free_3 = (char*)mymalloc(sizeof(char) * 54455480)))
		fprintf(file, "Probleme allocation\n");
	if(!(to_free_3 = (char*)mymalloc(sizeof(char) * 455480)))
		fprintf(file, "Probleme allocation\n");
	if(!(to_free_3 = (char*)mymalloc(sizeof(char) * 455480)))
		fprintf(file, "Probleme allocation\n");

	//show_alloc_mem();
	myfree(to_free_3);
	//show_alloc_mem();

	if(!(to_free_3 = (char*)mymalloc(sizeof(char) * 455480)))
		fprintf(file, "Probleme allocation\n");
	//show_alloc_mem();

	/*TINY ZONE*/
	while (i < 1926)
	{
		if(!(str = (char*)mymalloc(sizeof(char) * 512)))
			fprintf(file, "Probleme allocation\n");
		fprintf(file, "str 1 = %p\n\n############\n\n", str);
		i++;
	}
	if(!(to_free_1 = (char*)mymalloc(sizeof(char) * 256)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "to_free_1 = %p\n\n############\n\n", to_free_1);

	if(!(to_free_2 = (char*)mymalloc(sizeof(char) * 112)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "to_free_2 = %p\n\n############\n\n", to_free_2);

	if(!(to_free_3 = (char*)mymalloc(sizeof(char) * 80)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "to_free_3 = %p\n\n############\n\n", to_free_3);

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
	if(!(str3 = (char*)mymalloc(sizeof(char) * 83)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 3 = %p\n\n############\n\n", str3);
	b = (size_t)(str3);
	c = (size_t)(str3 + 81);
	str3[81] = '3';
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

	//test free and remalloc on space
	fprintf(file, "\n\n\n-oooooooOOOOOOOOooooooo-\n\nTest FREE AND REMALLOC ON SPACE\n\n\n");
	fprintf(file, "to_free_1 = %p\n\n############\n\n", to_free_1);
	myfree(to_free_1);
	myfree(to_free_3);
	myfree(to_free_2);
	if(!(str3 = (char*)mymalloc(sizeof(char) * 16)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 3 = %p\n\n############\n\n", str3);
	if(!(str3 = (char*)mymalloc(sizeof(char) * 224)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 3 = %p\n\n############\n\n", str3);
	if(!(str3 = (char*)mymalloc(sizeof(char) * 224)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 3 = %p\n\n############\n\n", str3);
	if(!(str3 = (char*)mymalloc(sizeof(char) * 224)))
		fprintf(file, "Probleme allocation\n");
	fprintf(file, "str 3 = %p\n\n############\n\n", str3);
	//show_alloc_mem();
	return (0);
}
