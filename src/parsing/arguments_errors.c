/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:51:42 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 01:29:37 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parsing.h"

static t_vector	*g_error_queue;

void	argument_error_free(t_argument_error *error_packet)
{
	free(error_packet->token);
	free(error_packet);
}

void	argument_error_queue_init(t_game *game)
{
	g_error_queue = vector_new();
	if (!g_error_queue)
		throw_error(ERROR_PARSING_ALLOC, game);
	g_error_queue->val_free = (void (*)(void *))argument_error_free;
}

void	argument_error_queue_clean(void)
{
	if (g_error_queue)
		vector_free(g_error_queue, true);
	g_error_queue = NULL;
}

bool	argument_error_register(int depth, t_error error, char *token,
			const t_argument *argument)
{
	t_argument_error	*error_packet;

	error_packet = malloc(sizeof(t_argument_error));
	if (!error_packet)
		return (false);
	error_packet->error = error;
	error_packet->depth = depth;
	error_packet->argument = *argument;
	error_packet->token = ft_strdup(token);
	if (!error_packet->token)
	{
		free(error_packet);
		return (false);
	}
	if (!vector_append(g_error_queue, error_packet))
	{
		free(error_packet->token);
		free(error_packet);
		return (false);
	}
	return (true);
}

void	argument_queue_print(void)
{
	unsigned int		index;
	t_argument_error	*error_packet;

	index = g_error_queue->total - 1;
	while (true)
	{
		error_packet = (t_argument_error *)g_error_queue->get(g_error_queue,
			index);
		if (!error_packet)
			return ;
		print_error_argument(error_packet->depth, error_packet->error,
			error_packet->token, &error_packet->argument);
		if (index == 0)
			return ;
		index--;
	}
}
