/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door_behaviors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 05:03:41 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

static inline void		door_activated_tick(t_entity *self, t_game *game);
static inline t_tile		*door_get_next_tile(t_entity_door_data *data,
							t_game *game);
static inline void		door_activate_all(t_entity_door_data *data,
							t_game *game);

void	entity_door_interacted(t_entity *self, t_game *game)
{
	t_entity_door_data	*data;

	data = (t_entity_door_data *)self->data;
	if (data->interacted)
		return ;
	if (game->entity_manager.interacted == self)
		game->entity_manager.interacted = NULL;
	data->interacted = true;
	self->transform.index = !self->transform.index;
	if (data->mode == 2)
		shuffle_indices(data->random_order, data->tiles_num, &game->rng);
}

void	entity_door_tick(t_entity *self, t_game *game)
{
	t_entity_door_data	*data;

	data = (t_entity_door_data *)self->data;
	if (!data->interacted)
		check_interaction(self, game);
	else
	{
		if (data->tiles_changed >= data->tiles_num)
		{
			if (!data->button)
				self->tick = NULL;
			data->tiles_changed = 0;
			data->interacted = false;
			data->speed = -data->speed;
		}
		else
			door_activated_tick(self, game);
	}
}

static inline void	door_activated_tick(t_entity *self, t_game *game)
{
	t_entity_door_data	*data;

	data = (t_entity_door_data *)self->data;
	if (data->mode == 0)
	{
		door_activate_all(data, game);
		return ;
	}
	if (data->actual == NULL)
		data->actual = door_get_next_tile(data, game);
	if (data->actual == NULL
		|| fabsf(data->actual_offset) >= data->offset)
	{
		data->actual = NULL;
		data->actual_offset = 0;
		data->tiles_changed++;
		return ;
	}
	data->actual->ceiling += data->speed;
	data->actual->floor += data->speed;
	data->actual_offset += data->speed;
}

static inline void	door_activate_all(t_entity_door_data *data, t_game *game)
{
	size_t	index;
	t_svec2	coord;

	if (fabsf(data->actual_offset) >= data->offset)
	{
		data->actual = NULL;
		data->actual_offset = 0;
		data->tiles_changed = data->tiles_num;
		return ;
	}
	index = 0;
	while (index < data->tiles_num)
	{
		coord = data->tiles[index];
		data->actual = tilemap_get_tile(coord.x, coord.y, game->tilemap);
		data->actual->ceiling += data->speed;
		data->actual->floor += data->speed;
		index++;
	}
	data->actual_offset += data->speed;
}

static inline t_tile	*door_get_next_tile(t_entity_door_data *data,
							t_game *game)
{
	t_svec2	coord;

	if (data->mode == 2)
		coord = data->tiles[data->random_order[data->tiles_changed]];
	else if (data->mode == 1)
		coord = data->tiles[data->tiles_changed];
	else
		coord = data->tiles[0];
	return (tilemap_get_tile(coord.x, coord.y, game->tilemap));
}
