/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:56:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 02:56:26 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	broadcast(char *str, t_game *game);

void	parse_property_broadcast(char *line, t_game *game)
{
	char	*event_data;

	event_data = ft_strdup(line + ft_strlen(g_property_token[PROP_BROADCAST]));
	if (!event_data)
		throw_error(ERROR_PARSING_ALLOC, game);
	if (!event_queue_push((void (*)(void *, t_game *))broadcast,
		event_data, true, game->events_postload))
	{
		free(event_data);
		throw_error(ERROR_PARSING_ALLOC, game);
	}
}

static const t_argument	g_argument_color[] = {
	{.name = "r", .type = DT_UINT, .limited = true, .int_max = 255},
	{.name = "g", .type = DT_UINT, .limited = true, .int_max = 255},
	{.name = "b", .type = DT_UINT, .limited = true, .int_max = 255},
	{.name = "visible", .type = DT_INT, .array = 2},
	{}
};

void	parse_property_color(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	static const t_property	property = {.name = "color",
		.args = g_argument_color};
	t_prop_inputs			*inputs;
	t_rgba8					*color;

	property_get_inputs(line, type, &property, game);
	inputs = &parsing->temp_inputs;
	if (type != PROP_A && inputs->argc == 4)
		throw_error_property(&property, ERROR_PROP_COLORS_ALPHA, game);
	if (type == PROP_C)
		color = &parsing->ceil_color;
	else if (type == PROP_A)
		color = &parsing->ambiant_color;
	else
		color = &parsing->floor_color;
	color->channels.r = *(int *)inputs->values[0];
	color->channels.g = *(int *)inputs->values[1];
	color->channels.b = *(int *)inputs->values[2];
	if (type == PROP_A && inputs->values[3])
		parsing->ambiant_strength = *(int *)inputs->values[3];
	else if (type == PROP_A)
		parsing->ambiant_strength = 5;
}

static const t_argument	g_argument_wall[] = {
	{.name = "path", .type = DT_STRING},
	{}
};

void	parse_property_wall(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	static const t_property	property = {.name = "wall",
		.args = g_argument_wall};
	int						cardinal;
	t_prop_inputs			*inputs;

	if (type == PROP_NO)
		cardinal = 0;
	else if (type == PROP_SO)
		cardinal = 1;
	else if (type == PROP_WE)
		cardinal = 2;
	else if (type == PROP_EA)
		cardinal = 3;
	else
		cardinal = 0;
	property_get_inputs(line, type, &property, game);
	inputs = &parsing->temp_inputs;
	parsing->textures_paths[cardinal] = (char *)inputs->values[0];
	inputs->values[0] = NULL;
}
