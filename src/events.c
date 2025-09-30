/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:34:29 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/01 00:05:57 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	event_free(t_event *event);

t_vector	*event_queue_init(t_game *game)
{
	t_vector	*result;

	result = vector_new();
	if (!result)
		throw_error(game, ERROR_ALLOC);
	result->val_free = (void (*)(void *))event_free;
	return (result);
}

void	event_queue_execute(t_vector *event_queue, t_game *game)
{
	unsigned int	index;
	t_event			*event;

	index = 0;
	while (index < event_queue->total)
	{
		event = (t_event *)event_queue->get(event_queue, index);
		if (!event)
			return ;
		if (event->call)
			event->call(event->ptr, game);
		index++;
	}
	while (index > 0)
	{
		event_queue->remove(event_queue, index - 1);
		index--;
	}
}

bool	event_queue_push(t_event_func call, void *ptr,
			bool to_free, t_vector *event_queue)
{
	t_event	*event;

	if (!event_queue)
		return (false);
	event = malloc(sizeof(t_event));
	if (!event)
		return (false);
	event->call = call;
	event->ptr = ptr;
	event->to_free = to_free;
	if (!event_queue->append(event_queue, event))
	{
		free(event);
		return (false);
	}
	return (true);
}

void	event_free(t_event *event)
{
	if (event->to_free)
		free(event->ptr);
	free(event);
}
