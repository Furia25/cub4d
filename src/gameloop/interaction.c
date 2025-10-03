/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:47:14 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 16:50:51 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_interactions(t_game *game)
{
	t_entity_manager	*entities;

	entities = &game->entity_manager;
	if (entities->can_interact && !entities->interacted
		&& key_is_pressed(KEY_INTERACT, game))
	{
		entities->interacted = entities->can_interact;
		if (entities->interacted->interaction)
			entities->interacted->interaction(entities->interacted, game);
	}
}

void	check_interaction(t_entity *self, t_game *game)
{
	float	distance;

	distance = vec3_distance2(self->position, game->player.position);
	if (distance < INTERACTION_RANGE && self->data)
		game->entity_manager.can_interact = self;
	else if (game->entity_manager.interacted == self
		|| game->entity_manager.can_interact == self)
	{
		game->entity_manager.interacted = NULL;
		game->render_textbox = false;
	}
}
