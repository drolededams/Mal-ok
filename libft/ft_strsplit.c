/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 19:18:43 by dgameiro          #+#    #+#             */
/*   Updated: 2016/12/16 16:11:58 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wrd_ct(const char *s, char c)
{
	int i;
	int ct;

	i = 0;
	ct = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			ct++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (ct);
}

static char		**get_letter(const char *s, char c, char **out)
{
	int i;
	int x;
	int y;

	i = 0;
	y = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		x = 0;
		while (s[i] && s[i] != c)
		{
			out[y][x] = s[i];
			x++;
			i++;
		}
		out[y][x] = '\0';
		y++;
	}
	if (s[i - 1] == c)
		free(out[--y]);
	out[y] = NULL;
	return (out);
}

char			**ft_strsplit(const char *s, char c)
{
	int		i;
	int		x;
	int		y;
	char	**out;

	i = 0;
	y = 0;
	if (!(out = (char**)malloc(sizeof(char*) * (ft_wrd_ct(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		x = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			x++;
		}
		if (!(out[y] = (char*)malloc(sizeof(char) * (x + 1))))
			return (NULL);
		y++;
	}
	return (get_letter(s, c, out));
}
