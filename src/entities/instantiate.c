/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instantiate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:58:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/07 06:07:07 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

static const t_argument		g_argument_npc[] = {
{.name = "text", .type = DT_STRING, .optional = true},
{}
};

static const t_argument		g_argument_door[] = {
{.name = "to_open", .type = DT_STRUCT, .subtype = SDT_TILE, .array = 1},
{.name = "offset", .type = DT_FLOAT, .limited = true,
	.fl_min = -HEIGHT_LIMIT, .fl_max = HEIGHT_LIMIT},
{.name = "speed", .type = DT_FLOAT, .limited = true, .fl_min = -5,
	.fl_max = 5},
{.name = "visible", .type = DT_ENUM, .subtype = SDT_BOOL, .optional = true},
{.name = "button", .type = DT_ENUM, .subtype = SDT_BOOL, .optional = true},
{.name = "mode", .type = DT_ENUM, .subtype = SDT_DOOR_TYPE, .optional = true},
{}
};

static const t_entity_ctx	g_entities_datas[] = {
[ENTITY_NPC] = {entity_new_npc, entity_npc_data,
{.name = "NPC Data", .args = g_argument_npc}},
[ENTITY_DOOR] = {entity_new_door, entity_door_data,
{.name = "DOOR Data", .args = g_argument_door}},
[ENTITY_TREE] = {entity_new_tree, NULL, {}},
[ENTITY_CAKE] = {entity_new_cake, NULL, {}}
};

void	entity_instantiate(t_entity_type type, t_vec3 position,
			t_prop_inputs *inputs, t_game *game)
{
	const t_entity_ctx	*constructors = &g_entities_datas[type];
	t_entity			*entity;
	t_prop_inputs		temp_inputs;
	t_error				data_error;

	entity = constructors->constructor(position, game);
	if (!entity)
		throw_error(ERROR_ENTITIES_ALLOC, game);
	entity_add(entity, game);
	if (inputs && constructors->data_constructor
		&& constructors->property.args)
	{
		temp_inputs = property_get_vla(inputs,
				&constructors->property, game);
		data_error = constructors->data_constructor(entity, temp_inputs, game);
		if (data_error != ERROR_NONE)
			throw_error(data_error, game);
	}
}
