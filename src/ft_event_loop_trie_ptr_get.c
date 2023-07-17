/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_loop_trie_ptr_get.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:45:41 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/17 15:13:17 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event_loop_internal.h"

typedef struct s_internal
{
	t_ft_event_loop_trie_ptr_key	key;
	void							**out_value;
}	t_internal;

static bool	internal(
	t_internal *context,
	t_ft_event_loop_trie_ptr_node *node,
	unsigned int level
)
{
	if (!node)
		return (false);
	if (level == sizeof(void *) - 1)
	{
		*context->out_value = node->children.leaf[context->key.num[level]];
		return (!!*context->out_value);
	}
	return (internal(context,
			node->children.non_leaf[context->key.num[level]], level + 1));
}

bool	ft_event_loop_trie_ptr_get(
	t_ft_event_loop_trie_ptr *self,
	void *key,
	void **out_value
)
{
	t_internal	context;

	context.key.ptr = key;
	context.out_value = out_value;
	return (internal(&context, self->root, 0));
}
