/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_entities.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:21:58 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/30 01:06:05 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENTITIES_H
# define CUB3D_ENTITIES_H
# include "cub3d.h"
# include "cub3d_rendering.h"

typedef struct s_entity
{
	t_sprite_sheet	sheet;
	t_vec2			position;
	t_bbox			hitbox;
	uint16_t		anim_index;
	uint16_t		state;
	bool			interactable;
	void			(*creation)(t_entity*, t_game*);
	void			(*update)(t_entity*, t_game*);
	void			(*interact)(t_entity*, t_game*);
	void			(*draw)(t_entity*, t_render_context*);
}	t_entity;

typedef struct s_living_component
{
	float		health;
	void		(*death)(t_entity*, t_game*);
	void		(*damage)(t_entity*, t_game*);
}	t_living_component;

#endif
