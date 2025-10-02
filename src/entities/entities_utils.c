/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:27:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 13:09:48 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_entities.h"

t_entity	*entity_new(t_game *game)
{
	t_entity	*result;

	result = ft_calloc(1, sizeof(t_entity));
	if (!result)
		throw_error(game, ERROR_ENTITIES_ALLOC);
	return (result);
}

void	entity_free(t_entity *entity)
{
	if (entity->free_data)
		entity->free_data(entity->data);
	free(entity);
}

void	entity_init_basics(t_vec3 position, t_entity *entity)
{
	entity->free_data = free;
	entity->position = position;
	entity->spr.spr_per_line = 1;
	entity->transform.color = g_colors[C_WHITE];
	entity->transform.width = 100;
	entity->transform.height = 200;
	entity->transform.index = 0;
	entity->transform.scale = 1;
	entity->transform.depth = 10000;
	entity->hitbox.min = (t_vec3){position.x - 0.2f,
		position.y - 0.2f, position.z - 0.4};
	entity->hitbox.max = (t_vec3){position.x + 0.2f,
		position.y + 0.2f, position.z};
	entity->map_color = g_colors[C_AZURE];
}
