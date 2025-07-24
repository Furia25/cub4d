/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:38:25 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/25 00:43:07 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"
#include <locale.h>

void	draw_interact_button(t_game *game, t_button *btn, int text_box)
{
	int				x;
	int				y;

	btn->color_light = rgba8(195, 195, 195, 255);
	btn->color_dark = rgba8(105, 105, 105, 255);
	btn->color_out = rgba8(255, 255, 255, 255);
	if (!text_box)
		btn->shadow_size = 15;
	else
		btn->shadow_size = 10;
	draw_button(game, btn);
	x = btn->x + (btn->width * 0.25);
	y = btn->y + (btn->height);
	if (!text_box)
		draw_text(L"»5~«E", (t_text_properties) \
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->frame);
	else
		draw_text(L"»3~«E", (t_text_properties) \
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->frame);
	x = game->w_halfwidth - 120;
	y = game->w_height * 0.90;
	if (!text_box)
		draw_text(L"»3*«interact", (t_text_properties) \
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->frame);
}

void	draw_textbox(t_game *game, char *text, uint64_t time)
{
	t_button		btn;
	int				x;
	int				y;
	wchar_t			w_text[TEXT_MAX_SIZE];

	setlocale(LC_ALL, "");
	mbstowcs(w_text, text, TEXT_MAX_SIZE);
	btn.color_light = g_colors[C_BEIGE];
	btn.color_dark = rgba8(157, 113, 83, 255);
	btn.color_out = rgba8(255, 255, 255, 255);
	btn.x = TXTBOX_X_START;
	btn.y = MINIMAP_Y_START;
	btn.width = MINIMAP_X_START;
	btn.height = MINIMAP_SIZE;
	btn.shadow_size = 15;
	draw_button(game, &btn);
	x = TXTBOX_X_START + 40;
	y = MINIMAP_Y_START + 40;
	draw_text(w_text, (t_text_properties){x, y, 0.8, 0, 0, 1, 75, \
		time}, game->frame);
	btn.x = 1775;
	btn.y = 950;
	btn.width = 60;
	btn.height = 60;
	draw_interact_button(game, &btn, 1);
}
