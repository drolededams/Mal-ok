/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgameiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:56:46 by dgameiro          #+#    #+#             */
/*   Updated: 2018/06/12 19:24:55 by dgameiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define T_RSIZE 1048576
# define S_RSIZE 8388608
# define T_MSIZE 512
# define S_MSIZE 15360
# define TINY 1
# define SMALL 2
# define LARGE 3
# define T_HEAD g_alloc.tiny
# define S_HEAD g_alloc.small
# define L_HEAD g_alloc.large
# define OVERFLOW_X ((size_t)1 << (sizeof(size_t) * 4))
# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/mman.h>

typedef struct		s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
	struct s_block	*prev;
}					t_block;

typedef struct		s_zone
{
	t_block			*head;
	t_block			*tail;
	struct s_zone	*prev;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_alloc
{
	t_zone		*tiny;
	t_zone		*small;
	t_block		*large;
}					t_alloc;

extern t_alloc g_alloc;
extern pthread_mutex_t g_mutex;

int					init_alloc(void);
size_t				set_zone_size(unsigned int type);
void				*set_zone(unsigned int type);
void				*malloc(size_t size);
void				*ts_malloc(t_zone *zone, unsigned int type, size_t size);
void				*l_malloc(t_block *block, size_t size);
void				*mmap_call(size_t	size);
void				*search_free_block(t_zone *zone,
		unsigned int type, size_t size);
void				*create_lblock(t_block *block, size_t size);
void				*split_block(t_zone *zone, t_block *block,
		unsigned int type, size_t size);
void				*expand_zone(t_zone *zone, unsigned int type, size_t size);
void				free(void *ptr);
void				free_defrag(t_zone *zone, t_block *block);
void				munmap_zone(t_zone *zone);
void				munmap_block(t_block *block);
t_zone				*is_in_zone(t_zone	*zone, t_block *wanted);
int					search_block(t_block *head, t_block *wanted);
void				*realloc(void *ptr, size_t size);
void				*t_realloc(void *ptr, size_t size,
		t_zone *zone, t_block *block);
void				*s_realloc(void *ptr, size_t size,
		t_zone *zone, t_block *block);
void				*l_realloc(void *ptr, size_t size, t_block *block);
void				*move_and_free(void *ptr, size_t old_size,
		size_t new_size);
int					enough_space(t_block *block, size_t size);
void				*fusion_block(t_zone *zone, int type,
		t_block *block, size_t size);
void				*ft_realloc_cpy(void *dst, const void *src,
		size_t n, size_t m);
void				show_alloc_mem(void);
void				print_add(void *add);
char				*add_to_str(unsigned long long add, char *hex);
int					add_len(unsigned long long add);
size_t				ts_print(t_zone *zone, int type);
size_t				l_print(t_block *block);
size_t				print_block(t_block *block);
void				ft_putsize_t(size_t n);
void				ft_putull(unsigned long long n);
void				*min_add(void *tiny, void *small, void *large);
unsigned long long	ull_max(unsigned long long t, unsigned long long s,
		unsigned long long l);
void				show_alloc_mem_hex(void);
unsigned long long	ts_print_hex(t_zone **zone, int *cur,
		unsigned long long line, unsigned char **str);
unsigned long long	l_print_hex(t_block *block, int *cur,
		unsigned long long line, unsigned char *s_pre, unsigned char *s_cur);
void				print_line_hex(unsigned long long line);
void				print_char_hex(unsigned long long c);
char				*char_to_str(unsigned long long c, char *hex);
char				*line_to_str(unsigned long long line, char *hex);
int					same_str(unsigned char *pre, unsigned char *cur);
void				str_cpy(unsigned char *pre, unsigned char *cur);
void				*calloc(size_t nmemb, size_t size);
void				*reallocf(void *ptr, size_t size);
void				*reallocarray(void *ptr, size_t n, size_t size);
void				print_total(unsigned long long total);
unsigned long long	print_zone(t_zone *tiny, t_zone *small,
		t_block *large, void *min);
unsigned char		**init_str_hex(void);
void				print_hex_zone(t_zone *tiny, t_zone *small,
		t_block *large, unsigned char **str);
unsigned long long	print_block_hex(t_block *block, int *cur,
		unsigned long long line, unsigned char **str);
void				print_all_hex(unsigned char **str, int *cur,
		unsigned long long line);
void				end_line(unsigned char **str, int *cur,
		unsigned long long line);
#endif
