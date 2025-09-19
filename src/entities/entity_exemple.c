/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_exemple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:23 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/19 16:40:36 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

void	entity_example_tick(t_entity *self, t_game *game);
void	entity_example_create(t_entity *self, t_game *game);

/*Entity constructor*/

t_entity	*entity_new_example(t_vec3 position, t_game *game)
{
	t_entity	*entity;
	t_png		*texture;

	entity = ft_calloc(1, sizeof(t_entity));
	if (!entity)
		throw_error(game, ERROR_ENTITIES_ALLOC);
	entity_init_basics(position, entity);
	texture = game->textures[TEXTURE_ENTITY_NPC];
	entity->transform.index = 1;
	entity->map_color = g_colors[C_ALICE_BLUE];
	entity->spr.asset = texture;
	entity->spr.spr_per_line = 2;
	entity->spr.width = 370;
	entity->spr.height = texture->header.height;
	entity->draw = entity_basic_draw;
	entity->tick = entity_example_tick;
	entity->create = entity_example_create;
	return (entity);
}

void	entity_example_tick(t_entity *self, t_game *game)
{
	self->transform.index = (self->transform.index + 1) % 2;
}

void	entity_example_create(t_entity *self, t_game *game)
{
}
