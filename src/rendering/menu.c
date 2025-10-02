/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:40:06 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/02 15:52:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"
#include "cub3d_rendering.h"

static char	*g_menu_options[] = {
	MENU_OPTION_RESUME,
	MENU_OPTION_CONFIG,
	MENU_OPTION_QUIT,
	NULL
};

static inline void	handle_menu_options(t_render_context *ctx, bool start,
						int x, int y)
{
	int				index;
	char			*temp;

	index = 0;
	while (index <= MENU_ACTIONS)
	{
		temp = g_menu_options[index];
		if (start && index == 0)
			temp = MENU_OPTION_PLAY;
		draw_text(temp, (t_text_properties){x, y + (125 * index),
			0.8, 0, 0, 1, 75, ctx->game->start_time}, ctx);
		index++;
	}
	draw_text("{5}>", (t_text_properties){x - 50,
		y + (125 * ctx->game->menu.action), 0.8,
		0, 0, 1, 75, ctx->game->start_time}, ctx);
	if (start)
		draw_text(GAME_NAME_F, (t_text_properties){ctx->render_width * 0.38,
			ctx->render_height * 0.25, 0.8, 0, 0, 1,
			75, ctx->game->start_time}, ctx);
}

void	handle_input(t_game *game, int start)
{
	int	input;

	input = (key_is_pressed(KEY_DOWN, game) - key_is_pressed(KEY_UP, game));
	input += (key_is_pressed(KEY_FLY_DOWN, game)
			- key_is_pressed(KEY_FLY_UP, game));
	game->menu.action = clamp(game->menu.action + input, 0, MENU_ACTIONS);
	if (key_is_released(KEY_ENTER, game))
	{
		if (game->menu.action == 0)
		{
			if (start)
				start_game(game);
			game->state = STATE_PLAYING;
		}
		if (game->menu.action == 2)
			exit_game(game);
	}
	if (key_is_pressed(KEY_PAUSE, game))
	{
		if (start)
			exit_game(game);
		else
			game->state = STATE_PLAYING;
	}
}

void	render_menu(int start, t_render_context *ctx, t_game *game)
{
	t_sprite_sheet	background;

	background.asset = game->textures[ASSET_BG_PAUSE];
	if (start)
		background.asset = game->textures[ASSET_BG_START];
	background.width = background.asset->header.width;
	background.height = background.asset->header.height;
	background.spr_per_line = 1;
	draw_spr_sheet((t_draw_transform){0, 0, game->frame->width,
		game->frame->height, g_colors[C_WHITE]}, 0, &background, game->frame);
	if (start)
		handle_menu_options(ctx, true, ctx->render_width * 0.43, ctx->halfh);
	else
	{
		draw_full_map(game);
		handle_menu_options(ctx, false, ctx->halfw, ctx->halfh);
	}
	handle_input(game, start);
}
