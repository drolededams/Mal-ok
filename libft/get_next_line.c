/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:39:26 by dgameiro          #+#    #+#             */
/*   Updated: 2016/11/03 12:19:35 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		ft_posc(char *str, int a)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)a)
			return (i);
		i++;
	}
	return (-1);
}

static void		ft_end_of_line(char *buf, t_file *cop, int red, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(red))
		return ;
	if (cop->str)
	{
		tmp = ft_strdup(cop->str);
		free(cop->str);
		cop->str = ft_strjoin(tmp, buf);
		free(tmp);
	}
	else
		cop->str = ft_strdup(buf);
	if (ft_posc(buf, '\n') == -1)
	{
		ft_bzero(buf, ft_strlen((const char*)buf));
		red = read(fd, buf, BUFF_SIZE);
		return (ft_end_of_line(buf, cop, red, fd));
	}
	return ;
}

static int		ft_cpy_line(char **line, t_file *cop)
{
	int		i;
	int		pos;
	char	*tmp;

	i = 0;
	if (cop->str && (pos = ft_posc(cop->str, '\n')) != -1)
	{
		tmp = ft_strdup(cop->str);
		free(cop->str);
		*line = ft_strsub(tmp, 0, pos);
		cop->str = ft_strsub(tmp, pos + 1, ft_strlen(tmp) - pos);
		if (!ft_strlen(cop->str))
			ft_memdel((void**)(&cop->str));
		free(tmp);
		return (1);
	}
	else if (cop->str)
	{
		tmp = ft_strdup(cop->str);
		ft_memdel((void**)(&cop->str));
		*line = ft_strdup(tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

static t_file	*ft_create_elem(t_file **begin, int fd)
{
	t_file *new;
	t_file *copy;

	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return (0);
	else
	{
		new->fd_num = fd;
		new->str = NULL;
		new->next = NULL;
		if (!(*begin))
		{
			*begin = new;
			copy = *begin;
		}
		else
		{
			copy = *begin;
			while (copy->next)
				copy = copy->next;
			copy->next = new;
			copy = copy->next;
		}
		return (copy);
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_file	*file;
	char			*buf;
	int				red;
	t_file			*copy;

	copy = file;
	if (!(buf = ft_memalloc(BUFF_SIZE + 1)) || BUFF_SIZE < 1 || fd < 0
	|| line == NULL || (red = read(fd, buf, BUFF_SIZE)) == -1)
		return (-1);
	buf[red] = 0;
	while (copy && copy->fd_num != fd)
		copy = copy->next;
	if (!copy)
		if (!(copy = ft_create_elem(&file, fd)))
			return (-1);
	if (red != 0)
		ft_end_of_line(buf, copy, red, fd);
	free(buf);
	return (ft_cpy_line(line, copy));
}
