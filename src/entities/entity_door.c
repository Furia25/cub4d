/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 19:38:01 by vdurand          ###   ########.fr       */
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
	entity->draw = (void (*)(struct s_entity *, void *))entity_basic_draw;
	entity->tick = entity_door_tick;
	entity->create = NULL;
	entity->interaction = entity_door_interacted;
	entity->free_data = free;
	entity->transform.height = 100;
	entity->transform.width = 50;
	return (entity);
}

/*Entity Data Constructor from parsed property*/

bool	entity_door_data(t_entity *self, t_property prop, t_game *game)
{
	t_entity_door_data	*temp_data;

	(void)game;
	if (prop.argc != 1)
		return (false);
	temp_data = malloc(sizeof(t_entity_door_data));
	if (!temp_data)
		return (false);
	temp_data->interacted = false;
	temp_data->offset = ft_atof(prop.argv[0]);
	temp_data->actual = 0;
	if (fabsf(temp_data->offset) >= HEIGHT_LIMIT)
	{
		free(temp_data);
		return (false);
	}
	self->data = temp_data;
	return (true);
}

void	entity_door_tick(t_entity *self, t_game *game)
{
	t_entity_door_data	*data;
	float				distance;

	data = (t_entity_door_data *)self->data;
	distance = vec3_distance2(self->position, game->player.position);
	if (distance < INTERACTION_RANGE && self->data)
		game->entity_manager.can_interact = self;
	else if (game->entity_manager.interacted == self
		|| game->entity_manager.can_interact == self)
		game->entity_manager.interacted = NULL;
	if (self->position.x < 0 || self->position.y < 0
			|| self->position.x >= game->tilemap->width
			|| self->position.y >= game->tilemap->height)
		return ;

void	entity_door_interacted(t_entity *self, t_game *game)
{
	t_entity_door_data	*data;
	const int			x_pos = (int)self->position.x;
	const int			y_pos = (int)self->position.y;

	if (!self->data)
		return ;
	data = (t_entity_door_data *)self->data;
	data->interacted = true;
	data->tile = &game->tilemap->tiles[y_pos][x_pos];
}
