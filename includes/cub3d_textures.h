/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:20:57 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/25 20:44:53 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TEXTURES_H
# define CUB3D_TEXTURES_H

# include "cub3d_structs.h"

# define STATE_MACHINE_MAX	5

/* TEXTURE_MISSING and TEXTURE_MAX_COUNT need to be first
and last respectively to assure correct behavior*/
typedef enum e_texture_type
{
	TEXTURE_ERROR,
	TEXTURE_WALL,
	TEXTURE_EAST,
	TEXTURE_WEST,
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_BOT,
	TEXTURE_WATER,
	TEXTURE_WATER0,
	TEXTURE_WATER1,
	TEXTURE_WATER2,
	TEXTURE_WATER3,
	TEXTURE_WATER4,
	TEXTURE_WATER5,
	TEXTURE_WATER6,
	TEXTURE_WATER7,
	TEXTURE_WATER8,
	TEXTURE_WATER9,
	TEXTURE_WATER10,
	TEXTURE_WATER11,
	TEXTURE_WATER12,
	TEXTURE_WATER13,
	TEXTURE_WATER14,
	TEXTURE_WATER15,
	TEXTURE_WATER16,
	TEXTURE_WATER17,
	TEXTURE_WATER18,
	TEXTURE_WATER19,
	TEXTURE_TOP,
	TEXTURE_GRASS,
	TEXTURE_ENTITY_NPC,
	TEXTURE_CIGARETTE,
	ASSET_BG_START,
	ASSET_BG_PAUSE,
	ASSET_SELECTOR,
	TEXTURE_MAX_COUNT
}	t_texture_type;

#define GLYPH_PATH	"assets/textures/glyph.png"

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
	bool			repeating;
}	t_index_animation;

extern const char	*g_textures_files[TEXTURE_MAX_COUNT];

t_index_animation	anim_index_init(size_t start_index, size_t end_index,
						float time_per_frame, float repeating);

void				anim_index_update(t_index_animation *anim);
void				anim_tile_update(t_tile_animation *anim, t_game *game);

#endif