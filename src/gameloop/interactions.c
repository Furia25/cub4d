/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:38:25 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/02 11:43:31 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"
#include <locale.h>

void	draw_interact_button(t_game *game, t_button *btn, int text_box)
{
	int				x;
	int				y;

	btn->color_light = g_colors[C_LIGHT_GRAY];
	btn->color_dark = g_colors[C_DARK_GRAY];
	btn->color_out = g_colors[C_DIM_GRAY];
	if (!text_box)
		btn->shadow_size = 15;
	else
		btn->shadow_size = 10;
	draw_button(game, btn);
	x = btn->x + (btn->width * 0.25);
	y = btn->y + (btn->height * 0.50);
	if (!text_box)
		draw_text(L"{5~}E", (t_text_properties)
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->frame);
	else
		draw_text(L"{3~}E", (t_text_properties)
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->frame);
	x = game->win.halfwidth - 120;
	y = game->win.height * 0.96;
	if (!text_box)
		draw_text(L"{3*}interact", (t_text_properties)
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->frame);
}

void	draw_textbox(t_game *game, char *text, uint64_t time, t_ivec2 pos)
{
	t_button		btn;
	int				x;
	int				y;

	btn.color_light = g_colors[C_BLANCHED_ALMOND];
	btn.color_dark = g_colors[C_BURLY_WOOD];
	btn.color_out = g_colors[C_DIM_GRAY];
	btn.x = pos.x;
	btn.y = pos.y;
	btn.width = 500;
	btn.height = MINIMAP_SIZE;
	btn.shadow_size = 15;
	draw_button(game, &btn);
	x = pos.x + 40;
	y = pos.y + 40;
	draw_text(text, (t_text_properties){x, y, 0.8, 0, 0, 1, 70,
		time}, game->frame);
	btn.x = 1775;
	btn.y = 950;
	btn.width = 60;
	btn.height = 60;
	btn.x += btn.width - btn.width - 2;
	btn.y += btn.height - btn.height - 2;
	draw_interact_button(game, &btn, 1);
}
