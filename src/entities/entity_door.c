/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 19:46:18 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	entity_door_tick(t_entity *self, t_game *game);
void	entity_door_interacted(t_entity *self, t_game *game);

/*Entity constructor*/

t_entity	*entity_new_door(t_vec3 position, t_game *game)
{
	t_entity	*entity;

	entity = entity_new(game);
	entity_init_basics(position, entity);
	entity->transform.index = 1;
	entity->map_color = g_colors[C_ALICE_BLUE];
	entity->draw = NULL;
	entity->tick = entity_door_tick;
	entity->create = NULL;
	entity->interaction = entity_door_interacted;
	entity->free_data = free;
	entity->transform.height = 100;
	entity->transform.width = 50;
	return (entity);
}

/*Entity Data Constructor from parsed property*/

t_error	entity_door_data(t_entity *self, t_prop_inputs prop)
{
	t_entity_door_data	*temp_data;

	temp_data = ft_calloc(1, sizeof(t_entity_door_data));
	if (temp_data)
	{
		free(temp_data);
		property_inputs_free(&prop);
		return (ERROR_PARSING_ALLOC);
	}
	temp_data->x_start = *((int *)prop.values[0]);
	temp_data->y_start = *((int *)prop.values[1]);
	temp_data->width = *((int *)prop.values[2]);
	temp_data->height = *((int *)prop.values[3]);
	temp_data->offset = *((float *)prop.values[4]);
	self->data = temp_data;
	return (ERROR_NONE);
}

static inline void	door_activated(t_entity *self, t_tilemap *tilemap);

void	entity_door_tick(t_entity *self, t_game *game)
{
	t_entity_door_data	*data;

	data = (t_entity_door_data *)self->data;
	if (!data->interacted)
		check_interaction(self, game);
	else
		door_activated(self, game->tilemap);
	if (fabsf(data->actual) >= fabsf(data->offset))
		self->tick = NULL;
}

static inline void	door_activated(t_entity *self, t_tilemap *tilemap)
{
	t_entity_door_data	*data;
	t_tile				*tile;
	int					x;
	int					y;

	data = (t_entity_door_data *)self->data;
	y = data->y_start;
	while (y != data->y_end)
	{
		x = data->x_start;
		while (x != data->x_end)
		{
			if (x > 0 || y > 0 || x < (int)tilemap->width
				|| y < (int)tilemap->height)
			{
				tile = &tilemap->tiles[y][x];
				if (tile->ceiling + data->speed > tile->floor)
					tile->ceiling = fclamp(tile->ceiling + data->speed,
						tile->floor + 0.01, HEIGHT_LIMIT);
			}
			x += sign(data->width);
		}
		y += sign(data->height);
	}
	data->actual += data->speed;
}

void	entity_door_interacted(t_entity *self, t_game *game)
{
	t_entity_door_data	*data;

	if (!self->data)
		return ;
	data = (t_entity_door_data *)self->data;
	data->interacted = true;
	data->actual = 0;
	data->x_end = data->x_start + data->width;
	data->y_end = data->y_start + data->height;
	if (game->entity_manager.interacted == self)
		game->entity_manager.interacted = NULL;
}
