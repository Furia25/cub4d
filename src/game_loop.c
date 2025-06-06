/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:10:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/06 21:24:55 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "mlx.h"
#include "mlx_int.h"

void	update_player(t_player *player, t_game *game)
{
	int	x_axis;
	int	y_axis;

	x_axis =  is_key_pressed(KEY_RIGHT, game) - is_key_pressed(KEY_LEFT, game);
	y_axis =  is_key_pressed(KEY_DOWN, game) - is_key_pressed(KEY_UP, game);
	printf("Player : %f, %f\n", player->position.x, player->position.y);
	player->position.x += (x_axis * player->speed);
	player->position.y += (y_axis * player->speed);
}

int	game_loop(void *param)
{
	t_game			*game;
	t_img_data		*frame;
	t_raycast_hit	raycast;

	game = param;
	frame = game->img;
	memset(frame->buffer, 0, frame->width * frame->height * (frame->pbits / 8));
	show_keys(game);
	handle_keys(game);
	update_player(&game->player, game);
	raycast = raycast_tilemap(, game->tilemap);
	img_draw_rect(rgba8(255, 255, 0, 255), rect_new(game->player.position, vec2_new(50, 50)), frame);
	mlx_put_image_to_window(game->mlx, game->win, frame->img_ptr, 0, 0);
	return (1);
}
