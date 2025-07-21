/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:20:57 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/21 20:43:04 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TEXTURES_H
# define CUB3D_TEXTURES_H

# include "cub3d_structs.h"

/* TEXTURE_MISSING and TEXTURE_MAX_COUNT need to be first and last respectively to assure correct behavior*/
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
	TEXTURE_TOP,
	TEXTURE_TEST,
	TEXTURE_GRASS,
	ASSET_BG_START,
	ASSET_BG_PAUSE,
	ASSET_SELECTOR,
	TEXTURE_MAX_COUNT
}	t_texture_type;

#define GLYPH_PATH	"assets/textures/glyph.png"

static char	*textures_files[TEXTURE_MAX_COUNT] = {
[TEXTURE_ERROR] = "assets/textures/missing.png",
[TEXTURE_WALL] = NULL,
[TEXTURE_GRASS] = "assets/textures/tiles/grass.png",
[TEXTURE_WATER] = "assets/textures/tiles/water.png",
[TEXTURE_TEST] = "assets/textures/tiles/4fdsfk.png",
[TEXTURE_TOP] = "assets/textures/tiles/wall_top.png",
[TEXTURE_BOT] = "assets/textures/tiles/wall_bot.png",
[TEXTURE_NORTH] = "1",
[TEXTURE_SOUTH] = "2",
[TEXTURE_WEST] = "3",
[TEXTURE_EAST] = "4",
[ASSET_BG_PAUSE] = "assets/textures/gui/bg_pause.png",
[ASSET_BG_START] = "assets/textures/gui/bg_start.png",
[ASSET_SELECTOR] = "assets/textures/gui/selector.png"
};

void	draw_sprite_sheet(t_draw_transform tform, size_t index,
			t_sprite_sheet *sprite, t_img_data *img);

#endif