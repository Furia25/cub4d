/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_anim.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 00:24:17 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/26 02:14:33 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ANIM_H
# define CUB3D_ANIM_H

# include "cub3d_textures.h"

typedef struct s_game	t_game;

typedef struct s_animated_texture
{
	float			actual_frame;
	float			frame_time;
	int				frames_num;
	t_png			*frames[32];
	t_texture_type	type;
}	t_tile_animation;

typedef struct s_index_animation
{
	float			actual_index;
	float			time_per_frame;
	size_t			start_index;
	size_t			end_index;
	float			anim_dir;
	bool			repeating;
	bool			reversing;
}	t_index_animation;

t_index_animation	anim_index_init(size_t start_index, size_t end_index,
						float time_per_frame, float repeating);

void				anim_tile_update(t_tile_animation *anim, t_game *game);
void				anim_index_update(t_index_animation *anim);
bool				anim_index_is_ended(t_index_animation *anim);

#endif