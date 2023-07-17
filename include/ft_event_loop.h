/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_loop.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:48:02 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2023/07/17 14:44:21 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVENT_LOOP_H
# define FT_EVENT_LOOP_H

# include <stddef.h>
# include <stdbool.h>

typedef bool			t_err;
typedef unsigned char	t_byte;

typedef struct s_ft_event_loop_options
{
	void	*(*malloc)(size_t size);
	void	*(*calloc)(size_t count, size_t size);
	void	(*free)(void *ptr);
}	t_ft_event_loop_options;

typedef struct s_ft_event_loop
{
	t_ft_event_loop_options	options;
}	t_ft_event_loop;

typedef enum e_ft_event_loop_task_result_type
{
	FT_EVENT_LOOP_TASK_RESULT_TYPE_AWAIT,
	FT_EVENT_LOOP_TASK_RESULT_TYPE_RETURN,
}	t_ft_event_loop_task_result_type;

typedef struct s_ft_event_loop_task_function
{
	struct s_ft_event_loop_task_function	*(*func)();
	t_ft_event_loop_task_result_type		type;
}	t_ft_event_loop_task_function;

typedef struct s_ft_event_loop_task
{
	void							*context;
	void							(*free_context)(void *context);
	t_ft_event_loop_task_function	function;
}	t_ft_event_loop_task;

t_ft_event_loop			*ft_event_loop_new(
							t_ft_event_loop options);

void					ft_event_loop_add_task(
							t_ft_event_loop *self,
							t_ft_event_loop_task task);

void					ft_event_loop_wait_until_end(void);

t_ft_event_loop_task	ft_event_loop_read_file(
							const char *filename,
							t_byte **out_buf,
							size_t *out_length);
t_ft_event_loop_task	ft_event_loop_write_file(
							const char *filename,
							t_byte *buf,
							size_t length);
t_ft_event_loop_task	ft_event_loop_append_file(
							const char *filename,
							t_byte *buf,
							size_t length);
t_ft_event_loop_task	ft_event_loop_open_directory(
							const char *dirname,
							int fd);

#endif
