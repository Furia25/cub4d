/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instantiate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:58:00 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 19:21:06 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

static const t_entity_ctx	g_entities_datas[ENTITY_MAX] = {
[ENTITY_DOOR] = {"DOOR", entity_new_door, entity_door_data, ERROR_ALLOC},
[ENTITY_NPC] = {"NPC", entity_new_npc, entity_npc_data, ERROR_ENTITY_NPC},
[ENTITY_TREE] = {"TREE", entity_new_tree, NULL, ERROR_ALLOC},
[ENTITY_UNKNOWN] = {"", NULL, NULL, 0}
};

void	entity_instantiate(t_entity_type type, t_vec3 position,
			t_prop_input *prop, t_game *game)
{
	const t_entity_ctx	*constructors = &g_entities_datas[type];
	t_entity			*entity;
	t_prop_input			temp_properties;

	if (type == ENTITY_UNKNOWN)
		return ;
	entity = constructors->constructor(position, game);
	if (!entity)
		throw_error(ERROR_ENTITIES_ALLOC, game);
	if (prop && constructors->data_constructor)
	{
		temp_properties = (t_prop_input){prop->argv + 4, prop->argc - 4};
		if (!constructors->data_constructor(entity, temp_properties, game))
		{
			entity_free(entity);
			throw_error(constructors->error, game);
		}
	}
	entity_add(entity, game);
}

t_entity_type	entity_get_from_token(const char *token)
{
	char	*entity_token;
	size_t	index;

	index = 0;
	while (token && index < ENTITY_MAX)
	{
		entity_token = g_entities_datas[index].token;
		if (entity_token && ft_strcmp(token, entity_token) == 0)
			return ((t_entity_type)index);
		index++;
	}
	return (ENTITY_UNKNOWN);
}
