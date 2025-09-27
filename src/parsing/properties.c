/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:56:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/27 02:35:40 by vdurand          ###   ########.fr       */
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
	
}

void	parse_property_wall(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	int		cardinal;
	size_t	index;
	size_t	lenght;

	if (type == PROP_NO)
		cardinal = 0;
	else if (type == PROP_SO)
		cardinal = 1;
	else if (type == PROP_WE)
		cardinal = 2;
	else if (type == PROP_EA)
		cardinal = 3;
	index = 0;
	property_pass_token(&index, type);
	while (line[index] && ft_isspace(line[index]))
		index++;
	parsing->textures_paths[cardinal] = line;
}

void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	
}
