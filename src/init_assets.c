/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:27:33 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/28 20:11:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "errno.h"
#include "glyphs.h"

void	init_hud(t_game *game)
{
	t_hud_cigarette	*hud_cigarette;
	t_sprite		*spr;

	hud_cigarette = &game->hud_cigarette;
	spr = &hud_cigarette->sprite;
	spr->sheet.asset = game->textures[TEXTURE_CIGARETTE];
	spr->sheet.width = 287;
	spr->sheet.height = 357;
	spr->sheet.spr_per_line = 19;
	spr->transform.x = 0;
	spr->transform.depth = -1;
	spr->transform.width = 538 * game->aspect_res;
	spr->transform.height = 673 * game->aspect_res;
	spr->transform.scale = 1;
	spr->transform.y = game->win.height - spr->transform.height;
	spr->transform.color = g_colors[C_WHITE];
	spr->transform.index = 0;
	hud_cigarette->equipped = false;
	hud_cigarette->anim_start = anim_index_init(0, 56, 1, false);
	hud_cigarette->anim_flex = anim_index_init(59, 138, 1, false);
	hud_cigarette->anim_idle_on = anim_index_init(138, 149, 0.8, true);
	hud_cigarette->anim_idle_off = anim_index_init(57, 59, 0.1, true);
	hud_cigarette->anim_idle_on.reversing = true;
	hud_cigarette->anim_idle_off.reversing = true;
}

int	init_assets(t_game *game)
{
	bool	temp;

	ft_putchar_fd('\n', 1);
	loading_log(false, NULL, NULL);
	game->textures[TEXTURE_ERROR]
		= png_open((char *)g_textures_files[TEXTURE_ERROR]);
	loading_log((game->textures[TEXTURE_ERROR] == NULL) * 2, NULL, NULL);
	if (!game->textures[TEXTURE_ERROR])
		throw_error(game, ERROR_LOADING_ASSETS);
	if (!init_textures(game))
		throw_error(game, ERROR_LOADING_ASSETS);
	temp = glyph_init(GLYPH_PATH);
	loading_log(!temp * 2, NULL, NULL);
	if (!temp)
		throw_error(game, ERROR_LOADING_GLYPHS);
	init_water(&game->water_anim, game);
	loading_log(0, NULL, NULL);
	if (game->textures[TEXTURE_GRASS] != game->textures[TEXTURE_ERROR])
		color_texture(game->textures[TEXTURE_GRASS], game->parsing.floor_color);
	loading_log(0, NULL, NULL);
	init_hud(game);
	loading_log(0, NULL, NULL);
	ft_putchar_fd('\n', 1);
	return (1);
}

int	init_textures(t_game *game)
{
	char		*path;
	int			index;
	int			parsed_index;

	index = 1;
	while (index < TEXTURE_MAX_COUNT)
	{
		path = (char *)g_textures_files[index];
		if (path != NULL)
		{
			parsed_index = ft_atoi(path);
			if (parsed_index != 0)
				path = game->parsing.textures_paths[parsed_index - 1];
			errno = 0;
			if (path != NULL)
				game->textures[index] = png_open(path);
			if (!game->textures[index])
				game->textures[index] = game->textures[TEXTURE_ERROR];
			loading_log(game->textures[index] == game->textures[TEXTURE_ERROR],
				WARNING_TEXTURE, path);
		}
		index++;
	}
	return (1);
}

void	init_water(t_tile_animation *water_anim, t_game *game)
{
	water_anim->type = TEXTURE_WATER;
	water_anim->frames_num = 20;
	water_anim->frame_time = 0.5;
	water_anim->actual_frame = 0;
	water_anim->frames[0] = game->textures[TEXTURE_WATER0];
	water_anim->frames[1] = game->textures[TEXTURE_WATER1];
	water_anim->frames[2] = game->textures[TEXTURE_WATER2];
	water_anim->frames[3] = game->textures[TEXTURE_WATER3];
	water_anim->frames[4] = game->textures[TEXTURE_WATER4];
	water_anim->frames[5] = game->textures[TEXTURE_WATER5];
	water_anim->frames[6] = game->textures[TEXTURE_WATER6];
	water_anim->frames[7] = game->textures[TEXTURE_WATER7];
	water_anim->frames[8] = game->textures[TEXTURE_WATER8];
	water_anim->frames[9] = game->textures[TEXTURE_WATER9];
	water_anim->frames[10] = game->textures[TEXTURE_WATER10];
	water_anim->frames[11] = game->textures[TEXTURE_WATER11];
	water_anim->frames[12] = game->textures[TEXTURE_WATER12];
	water_anim->frames[13] = game->textures[TEXTURE_WATER13];
	water_anim->frames[14] = game->textures[TEXTURE_WATER14];
	water_anim->frames[15] = game->textures[TEXTURE_WATER15];
	water_anim->frames[16] = game->textures[TEXTURE_WATER16];
	water_anim->frames[17] = game->textures[TEXTURE_WATER17];
	water_anim->frames[18] = game->textures[TEXTURE_WATER18];
	water_anim->frames[19] = game->textures[TEXTURE_WATER19];
}

void	color_texture(t_png *tex, t_rgba8 tint)
{
	size_t	x;
	size_t	y;
	t_rgba8	*pixel;

	if (tint.channels.r == 255 && tint.channels.g == 255 && tint.channels.b == 255)
		return ;
	y = 0;
	while (y < tex->header.height)
	{
		x = 0;
		while (x < tex->header.width)
		{
			pixel = (t_rgba8 *)&tex->pixels_8bit[y * tex->header.width + x];
			pixel->channels.r = lerp(pixel->channels.r, tint.channels.r, 0.4);
			pixel->channels.g = lerp(pixel->channels.g, tint.channels.g, 0.4);
			pixel->channels.b = lerp(pixel->channels.b, tint.channels.b, 0.4);
			x++;
		}
		y++;
	}
}
