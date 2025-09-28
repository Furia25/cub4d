/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:56:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/28 17:41:00 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_property_height(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	(void)line;
	(void)type;
	(void)parsing;
	(void)game;
}

void	parse_property_color(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	t_property	prop;
	t_rgba8		*color;

	prop = property_get_args(line, type, game);
	if (prop.argc < 3 || (prop.argc < 4 && type == PROP_A)
		|| (prop.argc > 3 && type != PROP_A) || prop.argc > 4
		|| !property_check_color(prop))
	{
		free_tab((void **)prop.argv);
		throw_error_info(game, ERROR_PARSING_PROPERTY, line);
	}
	if (type == PROP_C)
		color = &parsing->ceil_color;
	else if (type == PROP_A)
		color = &parsing->ambiant_color;
	else
		color = &parsing->floor_color;
	color->channels.r = ft_atoi(prop.argv[0]);
	color->channels.g = ft_atoi(prop.argv[1]);
	color->channels.b = ft_atoi(prop.argv[2]);
	if (type == PROP_A)
		parsing->ambiant_strength = ft_atoi(prop.argv[3]);
	free_tab((void **)prop.argv);
}

void	parse_property_wall(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	int			cardinal;
	t_property	prop;
	

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
	prop = property_get_args(line, type, game);
	if (prop.argc != 1)
	{
		free_tab((void **)prop.argv);
		throw_error_info(game, ERROR_PARSING_PROPERTY, line);
	}
	parsing->textures_paths[cardinal] = ft_strdup(prop.argv[0]);
	free_tab((void **)prop.argv);
	if (!parsing->textures_paths[cardinal])
		throw_error(game, ERROR_PARSING_ALLOC);
}

void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	(void)line;
	(void)type;
	(void)parsing;
	(void)game;
}
