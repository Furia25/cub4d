/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:42:49 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 18:57:09 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const t_argument	g_arguments_height[] = {
	{.name = "x", .type = DT_UINT},
	{.name = "y", .type = DT_UINT},
	{.name = "ceil_offset", .type = DT_FLOAT, .limited = true,
		.fl_min = -HEIGHT_LIMIT, .fl_max = HEIGHT_LIMIT},
	{.name = "floor_offset", .type = DT_FLOAT, .limited = true,
		.fl_min = -HEIGHT_LIMIT, .fl_max = HEIGHT_LIMIT, .optional = true},
	{}
};

static inline void	property_check_set_heights(t_height_data *data,
						t_prop_inputs *prop, t_game *game);

void	parse_property_height(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	static const 	t_property property = {.name = "HEIGHT",
		.args = g_arguments_height};
	t_prop_inputs	*prop;
	t_height_data	*event_data;

	parsing->temp_inputs = property_get_inputs(line, type, &property, game);
	prop = &parsing->temp_inputs;
	event_data = malloc(sizeof(t_height_data));
	if (!event_data)
		throw_error(ERROR_PARSING_ALLOC, game);
	event_data->precise = type == PROP_HEIGHT_PRECISE;
	property_check_set_heights(event_data, prop, game);
	if (!event_queue_push((void (*)(void *, t_game *))apply_height_postload,
		event_data, true, game->events_postload))
	{
		free(event_data);
		throw_error(ERROR_PARSING_ALLOC, game);
	}
}

static inline void	property_check_set_heights(t_height_data *data,
						t_prop_inputs *prop, t_game *game)
{
	data->x = *(int *)prop->values[0];
	data->y = *(int *)prop->values[1];
	data->width = *(int *)prop->values[2];
	data->height = *(int *)prop->values[3];
	data->ceil_offset = *(float *)prop->values[4];
	if (prop->values[5])
		data->floor_offset = *(float *)prop->values[5];
	else
		data->floor_offset = data->ceil_offset;
	if (data->floor_offset > data->ceil_offset && prop->argc == 6)
	{
		free(data);
		throw_error_property(prop->property, ERROR_PROP_HEIGHT_OFFSET, game);
	}
}

void	apply_height_postload(t_height_data *data, t_game *game)
{
	t_tile	*tile;
	int		i;
	int		j;

	if (data->x + data->width > game->parsing.map_width)
		data->width = game->parsing.map_width - data->x;
	if (data->y + data->height > game->parsing.map_height)
		data->height = game->parsing.map_height - data->y;
	if (data->ceil_offset == data->floor_offset && data->precise)
		data->ceil_offset += 0.05;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			tile = &game->tilemap->tiles[data->y + i][data->x + j];
			tile->ceiling = tile->ceiling * !data->precise + data->ceil_offset;
			tile->floor = tile->floor * !data->precise + data->floor_offset;
			if (is_symbol_player(game->parsing.map[data->y + i][data->x + j]))
				game->player.position.z = tile->ceiling;
			j++;
		}
		i++;
	}
}
