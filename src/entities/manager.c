/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:53:51 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/20 18:38:14 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

bool	entity_add(t_entity *entity, t_game *game)
{
	t_vector	*entities;

	if (!entity)
		return (false);
	entities = game->entity_manager.entities;
	if (!entities->append(entities, entity))
		return (false);
	entity->create(entity, game);
	return (true);
}

bool	entity_destroy(t_entity *entity, t_game *game)
{
	t_vector	*entities;
	long		index;

	if (!entity)
		return (false);
	entities = game->entity_manager.entities;
	entity->destroy(entity, game);
	index = entities->get_index(entities, entity);
	if (index == -1)
	{
		entity_free(entity);
		return (false);
	}
	if (!entities->remove(entities, index))
		return (false);
	return (true);
}
