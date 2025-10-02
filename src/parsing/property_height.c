/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:42:49 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 02:16:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline void	property_check_set_heights(char *line, t_height_data *data,
						t_property *prop, t_game *game);

void	parse_property_height(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	t_property		*prop;
	t_height_data	*event_data;

	parsing->temp_prop = property_get_args(line, type, game);
	prop = &parsing->temp_prop;
	if (!(prop->argc == 5 && type != PROP_HEIGHT_PRECISE) && prop->argc != 6)
		throw_error_info(game, ERROR_PROPERTY_HEIGHT, line);
	event_data = malloc(sizeof(t_height_data));
	if (!event_data)
		throw_error(game, ERROR_PARSING_ALLOC);
	event_data->precise = type == PROP_HEIGHT_PRECISE;
	property_check_set_heights(line, event_data, prop, game);
	if (!event_queue_push((void (*)(void *, t_game *))apply_height_postload,
		event_data, true, game->events_postload))
	{
		free(event_data);
		throw_error(game, ERROR_PARSING_ALLOC);
	}
}

static inline void	property_check_set_heights(char *line, t_height_data *data,
						t_property *prop, t_game *game)
{
	t_error	error;

	error = ERROR_NONE;
	data->x = ft_atoi(prop->argv[0]);
	data->y = ft_atoi(prop->argv[1]);
	data->width = ft_atoi(prop->argv[2]);
	data->height = ft_atoi(prop->argv[3]);
	data->ceil_offset = ft_atof(prop->argv[4]);
	if (prop->argc == 6)
		data->floor_offset = ft_atof(prop->argv[5]);
	else
		data->floor_offset = data->ceil_offset;
	if (data->floor_offset > data->ceil_offset && prop->argc == 6)
		error = ERROR_PROPERTY_HEIGHT_OFFSET;
	else if (data->x < 0 || data->y < 0|| data->width < 0 || data->height < 0)
		error = ERROR_PROPERTY_HEIGHT;
	else if (fabsf(data->floor_offset) > HEIGHT_LIMIT
		|| fabsf(data->ceil_offset) > HEIGHT_LIMIT)
		error = ERROR_PROPERTY_HEIGHT_LIMIT;
	if (error != ERROR_NONE)
	{
		free(data);
		throw_error_info(game, error, line);
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
