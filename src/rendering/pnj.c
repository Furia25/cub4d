/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pnj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:48:51 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/16 14:29:27 by halnuma          ###   ########.fr       */
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
	x = btn->x + (btn->width / 4);
	y = btn->y + (btn->height / 2);
	if (!text_box)
		draw_text(L"»5~«E", (t_text_properties) \
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->img);
	else
		draw_text(L"»3~«E", (t_text_properties) \
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->img);
	x = (WINDOW_WIDTH / 2) - 120;
	y = (WINDOW_HEIGHT / 2) + 80;
	if (!text_box)
		draw_text(L"»3*«interact", (t_text_properties) \
		{x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->img);
}

void	draw_textbox(t_game *game, char *text)
{
	t_button		btn;
	int				x;
	int				y;
	int				i;
	int				j;
	wchar_t			w_text[TEXT_MAX_SIZE];

	setlocale(LC_ALL, "" );
	mbstowcs(w_text, text, TEXT_MAX_SIZE);
	btn.color_light = rgba8(207, 185, 151, 255);
	btn.color_dark = rgba8(157, 113, 83, 255);
	btn.color_out = rgba8(255, 255, 255, 255);
	btn.x = TXTBOX_X_START;
	btn.y = MINIMAP_Y_START;
	btn.width = 1500;
	btn.height = MINIMAP_SIZE;
	btn.shadow_size = 15;
	draw_button(game, &btn);
	x = TXTBOX_X_START + 40;
	y = MINIMAP_Y_START + 40;
	i = 0;
	j = 0;
	draw_text(w_text, (t_text_properties){x, y, 0.8, 0, 0, 1, 75, \
		game->start_time}, game->img);
	btn.x = 1775;
	btn.y = 950;
	btn.width = 60;
	btn.height = 60;
	draw_interact_button(game, &btn, 1);
}

int	tablen(char **text)
{
	int	i;

	i = 0;
	while (text[i])
		i++;
	return (i);
}

void	manage_interaction(t_game *game, char **text)
{
	t_button		btn;

	if (is_key_pressed(KEY_INTERACT, game))
	{
		game->interaction++;
		usleep(100000);
	}
	if (!game->interaction)
	{
		btn.x = ((WINDOW_WIDTH / 2) - (S_BUTTON_INTERACT / 2));
		btn.y = ((WINDOW_HEIGHT / 2) - (S_BUTTON_INTERACT / 2));
		btn.width = S_BUTTON_INTERACT;
		btn.height = S_BUTTON_INTERACT;
		draw_interact_button(game, &btn, 0);
	}
	else if (game->interaction - 1 < tablen(text))
		draw_textbox(game, text[game->interaction - 1]);
	else if (game->interaction - 1 >= tablen(text))
		game->interaction = 0;
}

void	manage_pnjs(t_game *game)
{
	int		i;
	t_vec2	axis_dist;
	float	dist;
	int		pnj_in_range;

	i = 0;
	pnj_in_range = 0;
	while (i < game->pnj_count)
	{
		axis_dist = calculate_axis_dist(game->player.position, \
			game->pnjs[i].position);
		dist = calculate_distance(game->player.position, \
			game->pnjs[i].position, axis_dist);
		if (dist < INTERACTION_RANGE)
		{
			pnj_in_range = 1;
			manage_interaction(game, game->pnjs[i].text);
		}
		i++;
	}
	if (!pnj_in_range)
		game->interaction = 0;
}
