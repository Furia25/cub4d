/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:40:06 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/22 19:21:40 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"

static void	draw_text_menu(t_game *game, wchar_t *text, int x, int y)
{
	draw_text(text, (t_text_properties){x, y, 0.8, 0, 0, 1, 75, \
		game->start_time}, game->img);
	draw_text(L"»5«Quit", (t_text_properties){x, (y + 125), 0.8, 0, 0, 1, 75, \
		game->start_time}, game->img);
}

void	handle_input(t_game *game, int start)
{
	int	input;

	input = (key_is_pressed(KEY_DOWN, game) - key_is_pressed(KEY_UP, game));
	input += (key_is_pressed(KEY_TEST_DOWN, game) - \
	key_is_pressed(KEY_TEST_UP, game));
	game->menu.action = clamp(game->menu.action + input, 0, MENU_ACTIONS);
	if (key_is_released(KEY_ENTER, game))
	{
		if (game->menu.action == 0)
			game->state = PLAYING;
		else
			exit_game(game);
	}
	if (key_is_pressed(KEY_PAUSE, game))
	{
		if (start)
			exit_game(game);
		else
			game->state = PLAYING;
	}
}

void	render_menu(t_game *game, int start)
{
	t_png_pixel8	*background;

	if (start)
		background = game->textures[ASSET_BG_START]->pixels_8bit;
	else
		background = NULL;
	draw_sprite_sheet((t_draw_transform){});
	if (start)
	{
		draw_text_menu(game, L"»5«Play", 850, 550);
		draw_selector(game, 750, 525);
	}
	else
	{
		draw_full_map(game);
		draw_text_menu(game, L"»5«Resume", 1600, 100);
		draw_selector(game, 1500, 75);
	}
	handle_input(game, start);
}
