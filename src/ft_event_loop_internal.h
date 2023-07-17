/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_loop_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:17:16 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/17 15:06:44 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVENT_LOOP_INTERNAL_H
# define FT_EVENT_LOOP_INTERNAL_H

# include "ft_event_loop.h"

# include <limits.h>

# include <unistd.h>
# include <sys/select.h>

typedef union u_ft_event_loop_trie_ptr_key
{
	void	*ptr;
	t_byte	num[sizeof(void *)];
}	t_ft_event_loop_trie_ptr_key;

typedef union u_ft_event_loop_trie_ptr_children
{
	struct s_ft_event_loop_trie_ptr_node	*non_leaf[1 << CHAR_BIT];
	void									*leaf[1 << CHAR_BIT];
}	t_ft_event_loop_trie_ptr_children;

typedef struct s_ft_event_loop_trie_ptr_node
{
	size_t								children_count;
	t_ft_event_loop_trie_ptr_children	children;
}	t_ft_event_loop_trie_ptr_node;

typedef struct s_ft_event_loop_trie_ptr
{
	t_ft_event_loop_trie_ptr_node	*root;
}	t_ft_event_loop_trie_ptr;

typedef union u_ft_event_loop_trie_int_key
{
	int		i;
	t_byte	num[sizeof(int)];
}	t_ft_event_loop_trie_int_key;

typedef union u_ft_event_loop_trie_int_children
{
	struct s_ft_event_loop_trie_int_node	*non_leaf[1 << CHAR_BIT];
	void									*leaf[1 << CHAR_BIT];
}	t_ft_event_loop_trie_int_children;

typedef struct s_ft_event_loop_trie_int_node
{
	size_t								children_count;
	t_ft_event_loop_trie_int_children	children;
}	t_ft_event_loop_trie_int_node;

typedef struct s_ft_event_loop_trie_int
{
	t_ft_event_loop_trie_int_node	*root;
}	t_ft_event_loop_trie_int;

typedef struct s_ft_event_loop_internal
{
	t_ft_event_loop				external;
	fd_set						read_fds;
	fd_set						write_fds;
	t_ft_event_loop_trie_int	map_fd_to_task;
	t_ft_event_loop_trie_ptr	map_task_to_fd;
}	*t_ft_event_loop_internal;

t_ft_event_loop_trie_ptr	*ft_event_loop_trie_ptr_new(
								t_ft_event_loop_options *options);
t_err						ft_event_loop_trie_ptr_push(
								t_ft_event_loop_options *options,
								t_ft_event_loop_trie_ptr *self,
								void *key,
								void *value);
bool						ft_event_loop_trie_ptr_get(
								t_ft_event_loop_trie_ptr *self,
								void *key,
								void **out_value);
void						ft_event_loop_trie_ptr_pop(
								t_ft_event_loop_options *options,
								t_ft_event_loop_trie_ptr *self,
								void *key,
								void **out_value);

#endif
