/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_entities.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:21:58 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 11:36:01 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENTITIES_H
# define CUB3D_ENTITIES_H
# include "cub3d.h"
# include "cub3d_rendering.h"

typedef struct s_entity	t_entity;

typedef bool			(*t_entity_data_constructor)(t_entity*,
	t_property, t_game*);
typedef t_entity*		(*t_entity_constructor)(t_vec3, t_game*);

struct s_entity
{
	t_sprite_sheet				spr;
	t_transform					transform;
	t_vec3						position;
	t_bbox						hitbox;
	uint16_t					anim_index;
	uint16_t					state;
	void						(*create)(t_entity*, t_game*);
	void						(*tick)(t_entity*, t_game*);
	void						(*draw)(t_entity*, t_render_context*);
	void						(*destroy)(t_entity*, t_game*);
	void						(*free_data)(void *);
	void						*data;
	t_rgba8						map_color;
	bool						solid;
};

typedef struct s_entity_ctx
{
	char						*token;
	t_entity_constructor		constructor;
	t_entity_data_constructor	data_constructor;
	t_error						error;
}	t_entity_ctx;

t_entity	*entity_new(t_game *game);
void		entity_free(t_entity *entity);
bool		entity_add(t_entity *entity, t_game *game);
bool		entity_destroy(t_entity *entity, t_game *game);
void		entities_tick(t_game *game);
void		entities_draw(t_game *game, t_render_context *render);
void		entity_init_basics(t_vec3 position, t_entity *entity);
void		entity_basic_draw(t_entity *entity, t_render_context *render);

t_entity	*entity_new_npc(t_vec3 position, t_game *game);
bool		entity_npc_data(t_entity *self, t_property prop, t_game *game);

t_entity	*entity_new_tree(t_vec3 position, t_game *game);

#endif
