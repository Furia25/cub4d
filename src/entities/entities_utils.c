/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:27:54 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/21 01:30:56 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

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
	entity->sheet.sprite_per_line = 1;
	entity->map_color = g_colors[C_AZURE];
}
