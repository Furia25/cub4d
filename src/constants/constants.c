/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:23:49 by vdurand           #+#    #+#             */
/*   Updated: 2025/08/20 15:01:33 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*g_textures_files[TEXTURE_MAX_COUNT] = {
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
[ASSET_BG_START] = "assets/textures/gui/test.png",
[ASSET_SELECTOR] = "assets/textures/gui/selector.png"
};

const int	g_keymap[KEY_MAX_COUNT] = {
[KEY_QUIT] = XK_Escape,
[KEY_TEST] = XK_r,
[KEY_UP] = XK_w,
[KEY_DOWN] = XK_s,
[KEY_LEFT] = XK_a,
[KEY_RIGHT] = XK_d,
[KEY_JUMP] = XK_space,
[KEY_TAB] = XK_Tab,
[KEY_TEST_LEFT] = XK_Left,
[KEY_TEST_RIGHT] = XK_Right,
[KEY_TEST_DOWN] = XK_Down,
[KEY_TEST_UP] = XK_Up,
[KEY_INTERACT] = XK_e,
[KEY_PAUSE] = XK_F1,
[KEY_ENTER] = XK_Return
};

const t_rgba8	g_color_text[26] = {
{{.r = 0, .g = 0, .b = 0, .a = 255}},
{{.r = 255, .g = 255, .b = 255, .a = 255}},
{{.r = 255, .g = 0, .b = 0, .a = 255}},
{{.r = 0, .g = 255, .b = 0, .a = 255}},	
{{.r = 0, .g = 0, .b = 255, .a = 255}},
{{.r = 0, .g = 255, .b = 255, .a = 255}},
{{.r = 255, .g = 255, .b = 0, .a = 255}},
{{.r = 255, .g = 0, .b = 255, .a = 255}},
{{.r = 255, .g = 165, .b = 0, .a = 255}},
{{.r = 128, .g = 0, .b = 128, .a = 255}},
{{.r = 255, .g = 192, .b = 203, .a = 255}},
{{.r = 165, .g = 42, .b = 42, .a = 255}},
{{.r = 128, .g = 128, .b = 128, .a = 255}},
{{.r = 211, .g = 211, .b = 211, .a = 255}},
{{.r = 169, .g = 169, .b = 169, .a = 255}},
{{.r = 0, .g = 0, .b = 128, .a = 255}},
{{.r = 128, .g = 128, .b = 0, .a = 255}},
{{.r = 0, .g = 255, .b = 0, .a = 255}},
{{.r = 0, .g = 128, .b = 128, .a = 255}},
{{.r = 0, .g = 255, .b = 255, .a = 255}},
{{.r = 128, .g = 0, .b = 0, .a = 255}},
{{.r = 192, .g = 192, .b = 192, .a = 255}},
{{.r = 255, .g = 215, .b = 0, .a = 255}},
{{.r = 255, .g = 127, .b = 80, .a = 255}},
{{.r = 250, .g = 128, .b = 114, .a = 255}},
{{.r = 210, .g = 105, .b = 30, .a = 255}}
};

/*[TYPE] = 
type, 
texture, 
texture_topbot, 
solid,
wall,
visible,
blocking,
ceil_offset,
floor_offset,
name
*/

const t_tile_data	g_base_tile_info[TILE_MAX_COUNT] = {
[TILE_EMPTY] = {TILE_EMPTY, TEXTURE_GRASS, TEXTURE_GRASS, SOLID_ALL, false, false, false, 0, 0, "Empty"},
[TILE_WALL] = {TILE_WALL, TEXTURE_WALL, TEXTURE_TOP, SOLID_ALL, true, true, true, 0, 0, "Wall"},
[TILE_WATER] = {TILE_WATER, TEXTURE_WATER, TEXTURE_WATER, SOLID_FLOOR, false, true, true, -0.1, -0.15, "Water"},
};
