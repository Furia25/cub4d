/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 04:59:35 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void				entity_door_tick(t_entity *self, t_game *game);
void				entity_door_interacted(t_entity *self, t_game *game);
void				entity_door_free(void *ptr);

/*Entity constructor*/

t_entity	*entity_new_door(t_vec3 position, t_game *game)
{
	t_entity	*entity;

	entity = entity_new(game);
	entity_init_basics(position, entity);
	entity->transform.index = 1;
	entity->map_color = g_colors[C_CORAL];
	entity->draw = NULL;
	entity->tick = entity_door_tick;
	entity->create = NULL;
	entity->interaction = entity_door_interacted;
	entity->free_data = entity_door_free;
	entity->spr.width = 110;
	entity->spr.spr_per_line = 2;
	entity->transform.height = 50;
	entity->transform.width = 25;
	return (entity);
}

void	entity_door_postload(t_entity *self, t_game *game)
{
	const t_tilemap		*tilemap = game->tilemap;
	t_svec2				tile_coord;
	t_entity_door_data	*data;
	size_t				index;
	size_t				valids;

	data = (t_entity_door_data *)self->data;
	self->spr.asset = game->textures[TEXTURE_ENTITY_DOOR];
	self->spr.height = self->spr.asset->header.height;
	index = 0;
	valids = 0;
	while (index < data->tiles_num)
	{
		tile_coord = data->tiles[index];
		if (tile_coord.x < tilemap->width && tile_coord.y < tilemap->height)
			data->tiles[valids++] = tile_coord;
		index++;
	}
	data->tiles_num = valids;
}
