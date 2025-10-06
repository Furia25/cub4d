/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_entities.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:21:58 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/06 04:40:09 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENTITIES_H
# define CUB3D_ENTITIES_H

# include "cub3d_structs.h"
# include "cub3d_parsing.h"

typedef struct s_entity	t_entity;
typedef struct s_game	t_game;
typedef struct s_entity_manager	t_entity_manager;

typedef t_error			(*t_entity_data_constructor)(t_entity*, t_prop_inputs);
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
	void						(*draw)(t_entity*, void *);
	void						(*interaction)(t_entity *, t_game*);
	void						(*destroy)(t_entity*, t_game*);
	void						(*free_data)(void *);
	void						*data;
	t_rgba8						map_color;
	bool						solid;
};

typedef struct s_entity_manager
{
	t_vector	*entities;
	uint64_t	last_tick;
	t_entity	*interacted;
	t_entity	*can_interact;
	uint64_t	interaction_time;
}	t_entity_manager;

typedef struct s_entity_door_data
{
	int		x_start;
	int		y_start;
	int		width;
	int		height;
	float	offset;
	float	speed;
	float	actual;
	int		x_end;
	int		y_end;
	int		mode;
	bool	visible;
	bool	interacted;
}	t_entity_door_data;

typedef enum	s_entity_type
{
	ENTITY_NPC,
	ENTITY_DOOR,
	ENTITY_TREE,
	ENTITY_MAX
}	t_entity_type;

typedef struct s_entity_ctx
{
	char						*token;
	t_entity_constructor		constructor;
	t_entity_data_constructor	data_constructor;
	t_property					property;
}	t_entity_ctx;

void				entity_instantiate(t_entity_type type, t_vec3 position,
						t_prop_inputs *prop, t_game *game);

t_entity			*entity_new(t_game *game);
void				entity_free(t_entity *entity);
bool				entity_add(t_entity *entity, t_game *game);
bool				entity_destroy(t_entity *entity, t_game *game);
void				entities_tick(t_entity_manager *manager, t_game *game);
void				entity_init_basics(t_vec3 position, t_entity *entity);
void				check_interaction(t_entity *self, t_game *game);

t_entity			*entity_new_npc(t_vec3 position, t_game *game);
t_error				entity_npc_data(t_entity *self, t_prop_inputs prop);

t_entity			*entity_new_tree(t_vec3 position, t_game *game);

t_entity			*entity_new_door(t_vec3 position, t_game *game);
t_error				entity_door_data(t_entity *self, t_prop_inputs prop);

#endif
