/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_entities.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:21:58 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/13 18:27:14 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENTITIES_H
# define CUB3D_ENTITIES_H
# include "cub3d.h"
# include "cub3d_rendering.h"

typedef struct s_entity
{
	t_sprite_sheet	sheet;
	t_vec3			position;
	t_bbox			hitbox;
	uint16_t		anim_index;
	uint16_t		state;
	void			(*create)(t_entity*, t_game*);
	void			(*tick)(t_entity*, t_game*);
	void			(*draw)(t_entity*, t_render_context*);
	void			(*destroy)(t_entity*, t_game*);
	void			*data;
}	t_entity;

#endif
