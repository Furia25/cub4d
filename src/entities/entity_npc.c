/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:23 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 17:47:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_entities.h"

void	entity_npc_tick(t_entity *self, t_game *game);
void	entity_npc_create(t_entity *self, t_game *game);
bool	entity_npc_data(t_entity *self, t_property prop, t_game *game);

/*Entity constructor*/

t_entity	*entity_new_npc(t_vec3 position, t_game *game)
{
	t_entity	*entity;
	t_png		*texture;

	entity = entity_new(game);
	entity_init_basics(position, entity);
	texture = game->textures[TEXTURE_ENTITY_NPC];
	entity->transform.index = 1;
	entity->map_color = g_colors[C_ALICE_BLUE];
	entity->spr.asset = texture;
	entity->spr.spr_per_line = 2;
	entity->spr.width = 370;
	entity->spr.height = texture->header.height;
	entity->draw = entity_basic_draw;
	entity->tick = entity_npc_tick;
	entity->create = entity_npc_create;
	entity->free_data = free;
	entity->data_constructor = entity_npc_data;
	return (entity);
}

/*Entity Property Interpret*/

bool	entity_npc_data(t_entity *self, t_property prop, t_game *game)
{
	(void)game;
	if (prop.argc > 1)
		return (false);
	if (prop.argc == 0)
		return (true);
	self->data = ft_strdup(prop.argv[0]);
	if (!self->data)
		return (false);
	return (true);
}

void	entity_npc_tick(t_entity *self, t_game *game)
{
	(void)game;
	self->transform.index = (self->transform.index + 1) % 2;
}

void	entity_npc_create(t_entity *self, t_game *game)
{
	(void)game;
	(void)self;
}
