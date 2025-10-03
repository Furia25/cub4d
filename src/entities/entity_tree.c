/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:23 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 19:04:59 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	entity_tree_postload(t_entity *self, t_game *game);

/*Entity constructor*/

t_entity	*entity_new_tree(t_vec3 position, t_game *game)
{
	t_entity	*entity;

	entity = entity_new(game);
	entity_init_basics(position, entity);
	entity->transform.index = 0;
	entity->map_color = g_colors[C_GREEN];
	entity->draw = (void (*)(struct s_entity *, void *))entity_basic_draw;
	entity->tick = NULL;
	entity->create = NULL;
	entity->interaction = NULL;
	entity->transform.height = 400;
	entity->transform.width = 200;
	if (!event_queue_push((void (*)(void *, t_game *))entity_tree_postload,
		entity, false, game->events_postload))
	{
		free(entity);
		throw_error(ERROR_ENTITIES_ALLOC, game);
	}
	return (entity);
}

void	entity_tree_postload(t_entity *self, t_game *game)
{
	t_png	*texture;

	texture = game->textures[TEXTURE_ENTITY_TREE];
	self->spr.asset = texture;
	self->spr.spr_per_line = 1;
	self->spr.width = texture->header.width;
	self->spr.height = texture->header.height;
}
