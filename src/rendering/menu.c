/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:40:06 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/21 18:23:17 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"

static void	draw_background(t_game *game, t_png_pixel8 *background)
{
	int		i;
	int		j;
	t_rgba8	black;

	i = 0;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			if (!background)
				draw_pixel(black, j, i, game->img);
			else
				draw_pixel(background[(i * WINDOW_WIDTH) + j], j, i, game->img);
			j++;
		}
		i++;
	}
}

static void	draw_selector(t_game *game, int x, int y)
{
	uint32_t	i;
	uint32_t	j;
	t_png		*selector;

	selector = game->textures[ASSET_SELECTOR];
	y += game->menu.action * 125;
	i = 0;
	while (i < selector->header.height)
	{
		j = 0;
		while (j < selector->header.width)
		{
			draw_pixel(selector->pixels_8bit \
				[(i * selector->header.width) + j], x + j, y + i, game->img);
			j++;
		}
		i++;
	}
}

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
	draw_background(game, background);
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
