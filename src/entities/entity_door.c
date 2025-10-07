/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:20:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 04:43:28 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	entity_door_postload(t_entity *self, t_game *game);
void	entity_door_tick(t_entity *self, t_game *game);
void	entity_door_interacted(t_entity *self, t_game *game);
void	entity_door_free(void *ptr);

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

static inline bool	init_door_buffer(t_entity_door_data *data,
						const t_dt_array *array);
static inline void	init_door_values(t_entity_door_data *data,
						void **values, size_t argc);

/*Entity Data Constructor from parsed property*/

t_error	entity_door_data(t_entity *self, t_prop_inputs prop, t_game *game)
{
	const t_dt_array	*array = (t_dt_array *)prop.values[0];
	t_entity_door_data	*temp_data;

	self->data = ft_calloc(1, sizeof(t_entity_door_data));
	temp_data = (t_entity_door_data *)self->data;
	if (!self->data)
	{
		property_inputs_free(&prop);
		return (ERROR_PARSING_ALLOC);
	}
	ft_memset(temp_data, 0, sizeof(t_entity_door_data));
	if (!init_door_buffer(temp_data, array))
	{
		property_inputs_free(&prop);
		return (ERROR_PARSING_ALLOC);
	}
	init_door_values(temp_data, prop.values, prop.argc);
	property_inputs_free(&prop);
	if (temp_data->visible)
		self->draw = (t_entity_draw_event)entity_basic_draw;
	if (!event_queue_push((t_event_func)entity_door_postload, self,
			false, game->events_postload))
			throw_error(ERROR_ENTITIES_ALLOC, game);
	return (ERROR_NONE);
}

static inline bool	init_door_buffer(t_entity_door_data *data,
						const t_dt_array *array)
{
	size_t	index;

	data->tiles_num = array->length;
	data->tiles = ft_calloc(array->length, sizeof(t_svec2));
	if (!data->tiles)
		return (false);
	data->random_order = ft_calloc(array->length, sizeof(size_t));
	if (!data->random_order)
		return (false);
	index = 0;
	while (index < array->length)
	{
		data->random_order[index] = index;
		index++;
	}
	index = 0;
	while (index < array->length && array->values[index])
	{
		data->tiles[index] = sdt_get_tile(array->values[index]);
		index++;
	}
	return (true);
}

static inline void	init_door_values(t_entity_door_data *data,
						void **values, size_t argc)
{
	data->offset = *((float *)values[1]);
	data->speed = *((float *)values[2]);
	if (argc > 3 && values[3] != NULL)
		data->visible = *((bool *)values[3]);
	if (argc > 4 && values[4] != NULL)
		data->button = *((bool *)values[4]);
	if (argc > 5 && values[5] != NULL)
		data->mode = *((size_t *)values[5]);
}

void	entity_door_free(void *ptr)
{
	t_entity_door_data	*data;

	data = (t_entity_door_data *)ptr;
	if (data)
	{
		free(data->tiles);
		free(data->random_order);
	}
	free(data);
}
