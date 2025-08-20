/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:20:57 by halnuma           #+#    #+#             */
/*   Updated: 2025/08/20 17:52:52 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TEXTURES_H
# define CUB3D_TEXTURES_H

# include "cub3d_structs.h"

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
	TEXTURE_TOP,
	TEXTURE_TEST,
	TEXTURE_GRASS,
	ASSET_BG_START,
	ASSET_BG_PAUSE,
	ASSET_SELECTOR,
	TEXTURE_MAX_COUNT
}	t_texture_type;

#define GLYPH_PATH	"assets/textures/glyph.png"

extern const char	*g_textures_files[TEXTURE_MAX_COUNT];

#endif