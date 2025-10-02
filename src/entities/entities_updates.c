/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_updates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:50:05 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 05:40:34 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

void	entities_tick(t_game *game)
{
	uint64_t	time;
	size_t		i;
	t_vector	*entities;
	t_entity	*current;

	time = get_time_ms();
	if (time < game->entity_manager.last_tick)
		return ;
	game->entity_manager.last_tick = time + GAME_INTERVAL_MIN * 4;
	entities = game->entity_manager.entities;
	i = 0;
	while (i < entities->total)
	{
		current = ((t_entity *)entities->get(entities, i));
		if (!current)
			break ;
		if (current->tick)
			current->tick(current, game);
		i++;
	}
}

void	entities_draw(t_game *game, t_render_context *render)
{
	size_t		i;
	t_vector	*entities;
	t_entity	*current;

	entities = game->entity_manager.entities;
	i = 0;
	while (i < entities->total)
	{
		current = ((t_entity *)entities->get(entities, i));
		if (!current)
			break ;
		if (current->draw)
			current->draw(current, render);
		i++;
	}
}
