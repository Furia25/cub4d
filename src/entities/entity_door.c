/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 04:40:29 by vdurand          ###   ########.fr       */
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

	if (prop.argc != 6 || !ft_strcheck(prop.argv[0], ft_isdigit)
		|| !ft_strcheck(prop.argv[1], ft_isdigit)
		|| !ft_strcheck(prop.argv[2], ft_isdigit)
		|| !ft_strcheck(prop.argv[3], ft_isdigit)
		|| !ft_strcheck(prop.argv[4], is_fdigit)
		|| !ft_strcheck(prop.argv[4], is_fdigit))
		return (false);
	temp_data = ft_calloc(1, sizeof(t_entity_door_data));
	if (!temp_data)
		return (false);
	*temp_data = (t_entity_door_data){
		ft_atoi(prop.argv[0]), ft_atoi(prop.argv[1]),
		ft_atoi(prop.argv[2]), ft_atoi(prop.argv[3]),
		ft_atof(prop.argv[4]), ft_atof(prop.argv[5]), 0, false, 0, 0, 0, 0};
	if (fabsf(temp_data->offset) >= HEIGHT_LIMIT)
	{
		free(temp_data);
		return (false);
	}
	self->data = temp_data;
	return (true);
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
