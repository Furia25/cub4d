/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:23 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 03:41:04 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"

void	entity_npc_tick(t_entity *self, t_game *game);
bool	entity_npc_data(t_entity *self, t_prop_inputs prop, t_game *game);
void	entity_npc_postload(t_entity *self, t_game *game);
void	entity_npc_interacted(t_entity *self, t_game *game);

/*Entity constructor*/

t_entity	*entity_new_npc(t_vec3 position, t_game *game)
{
	t_entity	*entity;

	entity = entity_new(game);
	entity_init_basics(position, entity);
	entity->transform.index = 1;
	entity->map_color = g_colors[C_ALICE_BLUE];
	entity->draw = (void (*)(struct s_entity *, void *))entity_basic_draw;
	entity->tick = entity_npc_tick;
	entity->create = NULL;
	entity->interaction = entity_npc_interacted;
	entity->free_data = free;
	entity->transform.height = 100;
	entity->transform.width = 50;
	if (!event_queue_push((void (*)(void *, t_game *))entity_npc_postload,
		entity, false, game->events_postload))
	{
		free(entity);
		throw_error(ERROR_ENTITIES_ALLOC, game);
	}
	return (entity);
}

/*Entity Data Constructor from parsed property*/

bool	entity_npc_data(t_entity *self, t_prop_inputs prop, t_game *game)
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

void	entity_npc_postload(t_entity *self, t_game *game)
{
	t_png	*texture;

	texture = game->textures[TEXTURE_ENTITY_NPC];
	self->spr.asset = texture;
	self->spr.spr_per_line = 2;
	self->spr.width = 370;
	self->spr.height = texture->header.height;
}

void	entity_npc_tick(t_entity *self, t_game *game)
{
	check_interaction(self, game);
	if (game->entity_manager.interacted == self)
		self->transform.index = (self->transform.index + 1) % 2;
	else
		self->transform.index = 0;
}

void	entity_npc_interacted(t_entity *self, t_game *game)
{
	if (!self->data)
		return ;
	game->render_textbox = true;
	game->entity_manager.interaction_time = get_time_ms();
}
