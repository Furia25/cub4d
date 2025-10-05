/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instantiate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:58:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/05 17:36:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

static const t_entity_ctx	g_entities_datas[] = {
[ENTITY_DOOR] = {"DOOR", entity_new_door, entity_door_data, ERROR_ALLOC},
[ENTITY_NPC] = {"NPC", entity_new_npc, entity_npc_data, ERROR_ALLOC},
[ENTITY_TREE] = {"TREE", entity_new_tree, NULL, ERROR_ALLOC}
};

void	entity_instantiate(t_entity_type type, t_vec3 position,
			t_prop_inputs *inputs, t_game *game)
{
	const t_entity_ctx	*constructors = &g_entities_datas[type];
	t_entity			*entity;
	t_prop_inputs		temp_properties;

	entity = constructors->constructor(position, game);
	if (!entity)
		throw_error(ERROR_ENTITIES_ALLOC, game);
	if (inputs && constructors->data_constructor)
	{
		temp_properties = property_get_vla(inputs);
		if (!constructors->data_constructor(entity, temp_properties, game))
		{
			entity_free(entity);
			throw_error(constructors->error, game);
		}
	}
	entity_add(entity, game);
}
