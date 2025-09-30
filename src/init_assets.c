/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:27:33 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 23:23:27 by vdurand          ###   ########.fr       */
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
	hud_cigarette->anim_start = anim_init(0, 56, 1, false);
	hud_cigarette->anim_flex = anim_init(59, 138, 1, false);
	hud_cigarette->anim_idle_on = anim_init(138, 149, 0.8, true);
	hud_cigarette->anim_idle_off = anim_init(57, 59, 0.1, true);
	hud_cigarette->anim_idle_on.reversing = true;
	hud_cigarette->anim_idle_off.reversing = true;
}

int	init_assets(t_game *game)
{
	bool	temp;

	loading_log(false, NULL, NULL);
	game->textures[TEXTURE_ERROR]
		= png_open((char *)g_textures_files[TEXTURE_ERROR]);
	loading_log(!game->textures[TEXTURE_ERROR] * 2, NULL, NULL);
	if (!game->textures[TEXTURE_ERROR])
		throw_error_info(game, ERROR_LOADING_TEXTURES_FALLBACK,
			(char *)g_textures_files[TEXTURE_ERROR]);
	init_textures(game);
	temp = glyph_init(GLYPH_PATH);
	loading_log(!temp * 2, NULL, NULL);
	if (!temp)
		throw_error(game, ERROR_LOADING_GLYPHS);
	game->water_anim.type = TEXTURE_WATER;
	game->water_anim.index = anim_init(TEXTURE_WATER0,
		TEXTURE_WATER19, 0.4f, true);
	loading_log(0, NULL, NULL);
	if (game->textures[TEXTURE_GRASS] != game->textures[TEXTURE_ERROR])
		color_texture(game->textures[TEXTURE_GRASS], game->parsing.floor_color);
	loading_log(0, NULL, NULL);
	init_hud(game);
	loading_log(0, NULL, NULL);
	ft_putstr_fd("\n" LOADING_COMPLETE "\n", 1);
	return (1);
}

static inline void	textures_log(t_png *actual, char *path, t_game *game);

void	init_textures(t_game *game)
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
			textures_log(game->textures[index], path, game);
		}
		index++;
	}
}

static inline void	textures_log(t_png *actual, char *path, t_game *game)
{
	char	*warning;

	if (path != NULL
		&& (errno == ENOMEM || errno == ENFILE || errno == EMFILE))
	{
		loading_log(2, NULL, NULL);
		throw_error(game, ERROR_LOADING_TEXTURES_FATAL);
	}
	if (errno == ENAMETOOLONG)
		warning = WARNING_TEXTURE_NAME;
	else
		warning = WARNING_TEXTURE_ACCESS;
	loading_log(actual == game->textures[TEXTURE_ERROR], warning, path);
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
