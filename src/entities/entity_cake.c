/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_cake.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 05:59:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 12:43:24 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	entity_cake_tick(t_entity *self, t_game *game);
void	entity_cake_postload(t_entity *self, t_game *game);

/*Entity constructor*/

t_entity	*entity_new_cake(t_vec3 position, t_game *game)
{
	t_entity	*entity;

	entity = entity_new(game);
	entity_init_basics(position, entity);
	entity->transform.index = 0;
	entity->map_color = g_colors[C_GREEN];
	entity->draw = (t_entity_draw_event)entity_basic_draw;
	entity->tick = entity_cake_tick;
	entity->create = NULL;
	entity->interaction = NULL;
	entity->transform.height = 100;
	entity->transform.width = 100;
	if (!event_queue_push((t_event_func)entity_cake_postload,
			entity, false, game->events_postload))
	{
		free(entity);
		throw_error(ERROR_ENTITIES_ALLOC, game);
	}
	return (entity);
}

void	entity_cake_tick(t_entity *self, t_game *game)
{
	double	t;
	float	distance;

	t = get_elapsed_ms() / 1000.0;
	object_move((t_vec3){0, 0, sin(t) * 0.005}, &self->position, &self->hitbox);
	distance = vec3_distance(self->position, game->player.position);
	if (distance < 0.4)
	{
		printf(ANSI_BRIGHT_GREEN WIN_MESSAGE ANSI_RESET);
		exit_game(game);
	}
}

void	entity_cake_postload(t_entity *self, t_game *game)
{
	t_png	*texture;

	texture = game->textures[TEXTURE_ENTITY_CAKE];
	self->spr.asset = texture;
	self->spr.spr_per_line = 1;
	self->spr.width = texture->header.width;
	self->spr.height = texture->header.height;
}
