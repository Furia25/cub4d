/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:56:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/27 02:43:44 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_property_height(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	
}

void	parse_property_color(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	size_t	index;

	index = 0;
}

void	parse_property_wall(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	int		cardinal;
	size_t	index;
	size_t	length;

	if (type == PROP_NO)
		cardinal = 0;
	else if (type == PROP_SO)
		cardinal = 1;
	else if (type == PROP_WE)
		cardinal = 2;
	else if (type == PROP_EA)
		cardinal = 3;
	length = ft_strlen(line);
	if (length == 0)
		throw_error(game, ERROR_WTF);
	index = property_token_length(type);
	while (index < length && line[index] && ft_isspace(line[index]))
		index++;
	if (line[length - 1] == '\n')
		line[length - 1] = '\0';
	parsing->textures_paths[cardinal] = line + index;
}

void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	
}
