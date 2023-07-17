/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_loop_trie_ptr_new.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:38:09 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/17 14:39:15 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event_loop_internal.h"

t_ft_event_loop_trie_ptr	*ft_event_loop_trie_ptr_new(
	t_ft_event_loop_options *options
)
{
	return ((t_ft_event_loop_trie_ptr *)options->calloc(
			1, sizeof(t_ft_event_loop_trie_ptr)));
}
