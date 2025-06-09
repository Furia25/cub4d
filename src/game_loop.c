/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:10:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/09 16:38:14 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "mlx.h"
#include "mlx_int.h"

/*
if (key_pressed == KEY_UP)
		handle_dir_input(game, game->pos_x + (0.125 * game->direction.x), game->pos_y - (0.125 * game->direction.y), key_pressed);
	if (key_pressed == KEY_RIGHT)
		handle_dir_input(game, game->pos_x + (0.125 * game->direction.y), game->pos_y + (0.125 * game->direction.x), key_pressed);
	if (key_pressed == KEY_DOWN)
		handle_dir_input(game, game->pos_x - (0.125 * game->direction.x), + game->pos_y + (0.125 * game->direction.y), key_pressed);
	if (key_pressed == KEY_LEFT)
		handle_dir_input(game, game->pos_x - (0.125 * game->direction.y), game->pos_y - (0.125 * game->direction.x), key_pressed);*/

bool	tilemap_collision(float x, float y, t_tilemap *tilemap)
{
	t_tile	*tile;

	if (!tilemap_is_tile_valid(x, y, tilemap))
		return (true);
	tile = tilemap_get_tile((size_t) x, (size_t)  y, tilemap);
	printf("TEST : %ld, %ld, %d\n", (size_t) x, (size_t)  y, tile->info.solid);
	return (!tile->info.solid);
}
		
void	update_player(t_player *player, t_game *game)
{
	float	x_axis;
	float	y_axis;
	bool	collide;

	x_axis =  is_key_pressed(KEY_RIGHT, game) - is_key_pressed(KEY_LEFT, game);
	y_axis =  is_key_pressed(KEY_DOWN, game) - is_key_pressed(KEY_UP, game);
	x_axis = x_axis * player->speed;
	y_axis = y_axis * player->speed;
	printf("Player BBOX : %f, %f\n", player->collision_box.min.x + x_axis, player->collision_box.min.y + y_axis);
	collide = tilemap_collision(player->collision_box.min.x + x_axis, player->collision_box.min.y + y_axis, game->tilemap)
		&& tilemap_collision(player->collision_box.max.x + x_axis, player->collision_box.min.y + y_axis, game->tilemap)
		&& tilemap_collision(player->collision_box.min.x + x_axis, player->collision_box.max.y + y_axis, game->tilemap)
		&& tilemap_collision(player->collision_box.max.x + x_axis, player->collision_box.max.y + y_axis, game->tilemap);
	if (!collide)
		return ;
	player->position.x += x_axis;
	player->position.y += y_axis;
	player->collision_box.min.x += x_axis;
	player->collision_box.min.y += y_axis;
	player->collision_box.max.x += x_axis;
	player->collision_box.max.y += y_axis;
}

// static void raycast_test(double angle, t_game *game, t_img_data *frame)
// {
// 	t_ray2			ray;
// 	t_raycast_hit	raycast;

// 	ray = ray2_from_angle(game->player.position, deg_to_rad(angle));
// 	raycast = raycast_tilemap(&ray, game->tilemap);
// 	if (raycast.hitted)
// 	{
// 		img_draw_rect(rgba8(255, 255, 0, 255), rect_new(vec2_scale(ray2_point_at(ray, raycast.dist), 128), vec2_new(5, 5)), frame);
// 	}
// }

int	game_loop(void *param)
{
	t_game			*game;
	t_img_data		*frame;
	int				mouse_x;
	int				mouse_y;

	game = param;
	frame = game->img;
	memset(frame->buffer, 0, frame->width * frame->height * (frame->pbits / 8));
	show_keys(game);
	handle_keys(game);
	update_player(&game->player, game);
	draw_minimap(game);
	mlx_mouse_get_pos(game->mlx, game->win, &mouse_x, &mouse_y);
	mlx_put_image_to_window(game->mlx, game->win, frame->img_ptr, 0, 0);
	return (1);
}
