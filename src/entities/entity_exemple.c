/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_exemple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:23 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/03 21:12:18 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

/*Entity constructor*/

t_entity	*entity_new_example(t_vec3 position, t_game *game)
{
	t_entity	*entity;
	t_png		*texture;

	entity = ft_calloc(1, sizeof(t_entity));
	if (!entity)
		trow_error(game, ERROR_ENTITIES_ALLOC);
	entity_init_basics(position, entity);
	texture = game->textures[TEXTURE_ENTITY_NPC];
	entity->spr.asset = texture;
	entity->spr.sprite_per_line = 2;
	entity->spr.width = 370;
	entity->spr.height = texture->header.height;
	entity->draw = entity_basic_draw;
	return (entity);
}
