/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_anim.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 00:24:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/03 16:21:26 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ANIM_H
# define CUB3D_ANIM_H

# include "cub3d_textures.h"

typedef struct s_animation
{
	float			actual_index;
	float			time_per_frame;
	size_t			start_index;
	size_t			end_index;
	float			anim_dir;
	bool			repeating;
	bool			reversing;
}	t_animation;

typedef struct s_tile_animation
{
	t_animation		index;
	t_texture_type	type;
}	t_tile_animation;

t_animation	anim_init(size_t start_index, size_t end_index,
				float time_per_frame, float repeating);

void		anim_update(t_animation *anim);
bool		anim_is_ended(t_animation *anim);
void		anim_reset(t_animation *anim);

#endif