/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_loop_trie_ptr_pop.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:07:12 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/17 15:17:23 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event_loop_internal.h"

typedef struct s_internal
{
	t_ft_event_loop_options			*options;
	t_ft_event_loop_trie_ptr_key	key;
	void							**out_value;
}	t_internal;

static void	internal(
	t_internal *context,
	t_ft_event_loop_trie_ptr_node **node,
	unsigned int level
)
{
	if (!*node || !(*node)->children.leaf[context->key.num[level]])
		return ;
	if (level == sizeof(int) - 1)
	{
		if (context->out_value)
			*context->out_value
				= (*node)->children.leaf[context->key.num[level]];
		(*node)->children.leaf[context->key.num[level]] = NULL;
		if (--(*node)->children_count)
			return ;
		context->options->free(*node);
		*node = NULL;
		return ;
	}
	internal(context,
		&(*node)->children.non_leaf[context->key.num[level]], level + 1);
	if ((*node)->children.non_leaf[context->key.num[level]]
		|| --(*node)->children_count)
		return ;
	context->options->free(*node);
	*node = NULL;
}

void	ft_event_loop_trie_ptr_pop(
	t_ft_event_loop_options *options,
	t_ft_event_loop_trie_ptr *self,
	void *key,
	void **out_value
)
{
	t_internal	context;

	context.options = options;
	context.key.ptr = key;
	context.out_value = out_value;
	internal(&context, &self->root, 0);
}
