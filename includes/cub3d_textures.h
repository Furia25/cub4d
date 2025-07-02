/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:20:57 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/02 13:44:26 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TEXTURES_H
# define CUB3D_TEXTURES_H

# include "cub3d_structs.h"

typedef enum e_texture_type
{
	TEXTURE_NAN,
	TEXTURE_WALL,
	TEXTURE_EAST,
	TEXTURE_WEST,
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_TEST,
	TEXTURE_MAX_COUNT
}	t_texture_type;

typedef enum e_sprite_type
{
	SPRITE_ENEMY,
	SPRITE_MAX_COUNT
}	t_sprite_type;

typedef enum e_asset_type
{
	ASSET_BG_START,
	ASSET_BG_PAUSE,
	ASSET_SELECTOR,
	ASSET_MAX_COUNT
}	t_asset_type;

void	draw_sprite_sheet(t_draw_transform tform, size_t index,
			t_sprite_sheet *sprite, t_img_data *img);

#endif