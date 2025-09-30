/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:23:49 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 02:01:39 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*g_textures_files[TEXTURE_MAX_COUNT] = {
[TEXTURE_ERROR] = "assets/textures/missing.png",
[TEXTURE_WALL] = NULL,
[TEXTURE_GRASS] = "assets/textures/tiles/grass.png",
[TEXTURE_TOP] = "assets/textures/tiles/wall_top.png",
[TEXTURE_BOT] = "assets/textures/tiles/wall_bot.png",
[TEXTURE_NORTH] = "1",
[TEXTURE_SOUTH] = "2",
[TEXTURE_WEST] = "3",
[TEXTURE_EAST] = "4",
[TEXTURE_ENTITY_NPC] = "assets/textures/entity/npc.png",
[TEXTURE_WATER] = NULL,
[TEXTURE_CIGARETTE] = "assets/textures/cigarette.png",
[ASSET_BG_PAUSE] = "assets/textures/gui/bg_pause.png",
[ASSET_BG_START] = "assets/textures/gui/test.png",
[ASSET_SELECTOR] = "assets/textures/gui/selector.png",
[TEXTURE_WATER0] = "assets/textures/tiles/water/water0.png",
[TEXTURE_WATER1] = "assets/textures/tiles/water/water1.png",
[TEXTURE_WATER2] = "assets/textures/tiles/water/water2.png",
[TEXTURE_WATER3] = "assets/textures/tiles/water/water3.png",
[TEXTURE_WATER4] = "assets/textures/tiles/water/water4.png",
[TEXTURE_WATER5] = "assets/textures/tiles/water/water5.png",
[TEXTURE_WATER6] = "assets/textures/tiles/water/water6.png",
[TEXTURE_WATER7] = "assets/textures/tiles/water/water7.png",
[TEXTURE_WATER8] = "assets/textures/tiles/water/water8.png",
[TEXTURE_WATER9] = "assets/textures/tiles/water/water9.png",
[TEXTURE_WATER10] = "assets/textures/tiles/water/water10.png",
[TEXTURE_WATER11] = "assets/textures/tiles/water/water11.png",
[TEXTURE_WATER12] = "assets/textures/tiles/water/water12.png",
[TEXTURE_WATER13] = "assets/textures/tiles/water/water13.png",
[TEXTURE_WATER14] = "assets/textures/tiles/water/water14.png",
[TEXTURE_WATER15] = "assets/textures/tiles/water/water15.png",
[TEXTURE_WATER16] = "assets/textures/tiles/water/water16.png",
[TEXTURE_WATER17] = "assets/textures/tiles/water/water17.png",
[TEXTURE_WATER18] = "assets/textures/tiles/water/water18.png",
[TEXTURE_WATER19] = "assets/textures/tiles/water/water19.png"
};

const char *g_property_token[PROP_UNKNOWN] = {
[PROP_NO] = "NO ",
[PROP_SO] = "SO ",
[PROP_WE] = "WE ",
[PROP_EA] = "EA ",
[PROP_F] = "F ",
[PROP_C] = "C ",
[PROP_A] = "A ",
[PROP_ENTITY] = "ENTITY ",
[PROP_HEIGHT] = "HEIGHT ",
[PROP_BROADCAST] = "##",
[PROP_COMMENT] = "#"
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
[KEY_LOOK_LEFT] = XK_Left,
[KEY_LOOK_RIGHT] = XK_Right,
[KEY_FLY_DOWN] = XK_Down,
[KEY_FLY_UP] = XK_Up,
[KEY_INTERACT] = XK_e,
[KEY_PAUSE] = XK_F1,
[KEY_GRAVITY] = XK_g,
[KEY_ENTER] = XK_Return,
[KEY_FLEX] = XK_f
};

/*[TYPE] = 
type, 
texture, 
texture_topbot, 
solid,
wall,
visible,
ceil_offset,
floor_offset,
name
*/

const t_tile_data	g_base_tile_info[TILE_MAX] = {
[TILE_EMPTY] = {TILE_EMPTY, TEXTURE_ERROR, TEXTURE_ERROR, SOLID_NONE, false, -5, -6, "Empty"},
[TILE_GRASS] = {TILE_GRASS, TEXTURE_GRASS, TEXTURE_GRASS, SOLID_ALL, true, 0, 0, "Empty"},
[TILE_WALL] = {TILE_WALL, TEXTURE_WALL, TEXTURE_TOP, SOLID_ALL, true, 1.5, 0, "Wall"},
[TILE_WATER] = {TILE_WATER, TEXTURE_WATER, TEXTURE_WATER, SOLID_FLOOR, true, -0.1, -0.15, "Water"},
};
