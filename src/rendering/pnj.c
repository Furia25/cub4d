/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pnj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:48:51 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/27 13:56:07 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "glyphs.h"

void	draw_textbox(t_game *game)
{
	t_button		btn;
	int				x;
	int				y;

	btn.color_light = rgba8(207, 185, 151, 255);
	btn.color_dark = rgba8(157, 113, 83, 255);
	btn.color_out = rgba8(255, 255, 255, 255);
	btn.x = TXTBOX_X_START;
	btn.y = MINIMAP_Y_START;
	btn.width = 1500;
	btn.height = MINIMAP_SIZE;
	draw_button(game, &btn);
	x = TXTBOX_X_START + 40;
	y = MINIMAP_Y_START + 40;
	draw_text(L"»2T«Yo la team comment ca va hahaha en gros la je fais un test de \
		texte de pnj letsgo juste entrain d'ecrire au hasard la", \
		(t_text_properties){x, y, 0.8, 0, 0, 1, 75, game->start_time}, \
		game->img);
}

void	draw_interact_button(t_game *game)
{
	t_button		btn;
	int				x;
	int				y;

	btn.color_light = rgba8(195, 195, 195, 255);
	btn.color_dark = rgba8(105, 105, 105, 255);
	btn.color_out = rgba8(255, 255, 255, 255);
	btn.x = ((WINDOW_WIDTH / 2) - (S_BUTTON_INTERACT / 2));
	btn.y = ((WINDOW_HEIGHT / 2) - (S_BUTTON_INTERACT / 2));
	btn.width = S_BUTTON_INTERACT;
	btn.height = S_BUTTON_INTERACT;
	draw_button(game, &btn);
	x = btn.x + (S_BUTTON_INTERACT / 4);
	y = btn.y + (S_BUTTON_INTERACT / 2);
	draw_text(L"»5~«E", \
	(t_text_properties){x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->img);
	x = (WINDOW_WIDTH / 2) - 120;
	y = (WINDOW_HEIGHT / 2) + 80;
	draw_text(L"»3*«interact", \
	(t_text_properties){x, y, 0.8, 0, 0, 1, 16, game->start_time}, game->img);
}

void	manage_interaction(t_game *game)
{
	if (is_key_pressed(KEY_INTERACT, game))
		game->interacting = true;
	if (!game->interacting)
		draw_interact_button(game);
	else
		draw_textbox(game);
}

void	manage_pnjs(t_game *game)
{
	int		i;
	t_vec2	axis_dist;
	float	dist;
	int		pnj_in_range;

	i = 0;
	pnj_in_range = 0;
	while (i < game->enemy_count)
	{
		axis_dist = calculate_axis_dist(game->player.position, \
			game->enemies[i].position);
		dist = calculate_distance(game->player.position, \
			game->enemies[i].position, axis_dist);
		if (dist < INTERACTION_RANGE)
		{
			pnj_in_range = 1;
			manage_interaction(game);
		}
		i++;
	}
	if (!pnj_in_range)
		game->interacting = false;
}
