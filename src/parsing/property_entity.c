/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 03:02:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 04:01:01 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

static const t_argument	g_arguments_entity[] = {
	{.name = "entity", .type = DT_ENUM, .subtype = SDT_ENTITY},
	{.name = "pos", .type = DT_STRUCT, .subtype = SDT_VEC3},
	{}
};

void	parse_property_entity(char *line, t_property_type type,
			t_parsing *parsing, t_game *game)
{
	static const t_property 	property = {.name = "ENTITY",
		.variable = true, .args = g_arguments_entity};
	t_prop_inputs		*inputs;
	t_entity_type		entity_type;
	t_vec3				pos;

	property_get_inputs(line, type, &property, game);
	inputs = &parsing->temp_inputs;
	entity_type = *(t_entity_type *)inputs->values[0];
	pos = dt_get_vec3(inputs->values[1]);
	entity_instantiate(entity_type, pos, inputs, game);
}
