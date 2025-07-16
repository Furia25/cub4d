/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:40:06 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/16 10:14:07 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"

static void	draw_backround(t_game *game, t_png_pixel8 *background)
{
	int				i;
	int				j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
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

	selector = game->menu.assets[ASSET_SELECTOR];
	if (!game->menu.action)
		y += 125;
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

void	render_start_menu(t_game *game)
{
	t_png_pixel8	*background;

	background = game->menu.assets[ASSET_BG_START]->pixels_8bit;
	draw_backround(game, background);
	draw_text_menu(game, L"»5«Play", 850, 550);
	draw_selector(game, 750, 525);
	if (is_key_pressed(KEY_TEST_DOWN, game) || is_key_pressed(KEY_DOWN, game))
		game->menu.action = false;
	if (is_key_pressed(KEY_TEST_UP, game) || is_key_pressed(KEY_UP, game))
		game->menu.action = true;
	if (is_key_pressed(KEY_ENTER, game))
	{
		if (game->menu.action)
			game->state = PLAYING;
		else
			exit_game(game);
	}
}

void	render_pause_menu(t_game *game)
{
	t_png_pixel8	*background;

	background = game->menu.assets[ASSET_BG_PAUSE]->pixels_8bit;
	draw_backround(game, background);
	draw_full_map(game);
	draw_text_menu(game, L"»5«Resume", 850, 550);
	draw_selector(game, 750, 525);
	if (is_key_pressed(KEY_TEST_DOWN, game) || is_key_pressed(KEY_DOWN, game))
		game->menu.action = false;
	if (is_key_pressed(KEY_TEST_UP, game) || is_key_pressed(KEY_UP, game))
		game->menu.action = true;
	if (is_key_pressed(KEY_ENTER, game))
	{
		if (game->menu.action)
			game->state = PLAYING;
		else
			exit_game(game);
	}
}
