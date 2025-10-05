/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 03:02:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 17:50:11 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	t_prop_inputs	prop;
	t_entity_type	entity_type;
	t_vec3			pos;

	prop = property_get_inputs(line, type, NULL, game);
	parsing->temp_prop = prop;
	entity_type = *(t_entity_type *)prop.values[0];
	pos = dt_get_vec3(prop.values[1]);
	entity_instantiate(entity_type, pos, &prop, game);
}
