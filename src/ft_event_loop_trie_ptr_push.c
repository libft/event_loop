/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_loop_trie_ptr_push.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:25:12 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/17 15:13:26 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event_loop_internal.h"

typedef struct s_internal
{
	t_ft_event_loop_options			*options;
	t_ft_event_loop_trie_ptr_key	key;
	void							*value;
}	t_internal;

static t_err	internal(
	t_internal *context,
	t_ft_event_loop_trie_ptr_node **node,
	unsigned int level
)
{
	bool	result;

	if (!*node)
		*node = context->options->calloc(
				1, sizeof(t_ft_event_loop_trie_ptr_node));
	if (!*node)
		return (true);
	if (level == sizeof(void *) - 1)
	{
		(*node)->children.leaf[context->key.num[level]] = context->value;
		(*node)->children_count++;
		return (false);
	}
	result = internal(context,
			&(*node)->children.non_leaf[context->key.num[level]], level + 1);
	if ((*node)->children.non_leaf[context->key.num[level]])
		(*node)->children_count++;
	if (!(*node)->children_count)
	{
		context->options->free(*node);
		*node = NULL;
	}
	return (result);
}

t_err	ft_event_loop_trie_ptr_push(
	t_ft_event_loop_options *options,
	t_ft_event_loop_trie_ptr *self,
	void *key,
	void *value
)
{
	t_internal	context;

	context.options = options;
	context.key.ptr = key;
	context.value = value;
	return (internal(&context, &self->root, 0));
}
