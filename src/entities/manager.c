/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:53:51 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 17:13:12 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

bool	entity_add(t_entity *entity, t_game *game)
{
	t_vector	*entities;

	if (!entity)
		throw_error(game, ERROR_ENTITIES_INVALID);
	entities = game->entity_manager.entities;
	if (!entities->append(entities, entity))
	{
		entity_free(entity);
		throw_error(game, ERROR_ENTITIES_ALLOC);
	}
	if (entity->create)
		entity->create(entity, game);
	return (true);
}

bool	entity_destroy(t_entity *entity, t_game *game)
{
	t_vector	*entities;
	long		index;

	if (!entity)
		throw_error(game, ERROR_ENTITIES_INVALID);
	entities = game->entity_manager.entities;
	if (entity->destroy)
		entity->destroy(entity, game);
	index = entities->get_index(entities, entity);
	if (index == -1)
	{
		entity_free(entity);
		throw_error(game, ERROR_ENTITIES_INVALID);
	}
	if (!entities->remove(entities, index))
		throw_error(game, ERROR_ENTITIES_ALLOC);
	return (true);
}
