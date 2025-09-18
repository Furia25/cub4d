/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:47:18 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/18 19:00:00 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "maths2_easing.h"

void	player_move_collision(t_vec3 move, t_player *player, t_game *game)
{
	t_vec3	temp_v;

	temp_v = vec3_new(move.x, 0, 0);
	if (!tilemap_collide_bbox(temp_v, player->bbox, game->tilemap))
		player_add_x(move.x, player);
	temp_v = vec3_new(0, move.y, 0);
	if (!tilemap_collide_bbox(temp_v, player->bbox, game->tilemap))
		player_add_y(move.y, player);
}

void	player_handle_jump(t_player *plr, t_game *game)
{
	const float	gravity = -0.013f;
	bool		jumping;

	jumping = key_check(KEY_JUMP, game);
	if (jumping && plr->is_grounded)
	{
		plr->is_grounded = false;
		plr->jump_velocity = plr->jump_force;
	}
	plr->jump_velocity += gravity;
	if (/*!(plr->jump_velocity < 0 && plr->bbox.min.z <= plr->eye_height)
		&& */!tilemap_collide_bbox((t_vec3){0, 0, plr->jump_velocity},
			plr->bbox, game->tilemap))
		player_add_z(plr->jump_velocity, plr);
	else
		plr->jump_velocity = 0.0f;
	if (plr->bbox.min.z <= plr->eye_height
		|| tilemap_collide_bbox((t_vec3){0, 0, -0.1}, plr->bbox, game->tilemap))
		plr->is_grounded = true;
}

void	update_player(t_player *player, t_game *game)
{
	float	fly;
	float	forward;
	float	strafe;
	t_vec2	dir;
	t_vec2	move;

	strafe =  key_check(KEY_RIGHT, game) - key_check(KEY_LEFT, game);
	forward =  key_check(KEY_UP, game) - key_check(KEY_DOWN, game);
	player->yaw_rad += (M_PI / 100) * (key_check(KEY_TEST_RIGHT, game) - key_check(KEY_TEST_LEFT, game));
	game->player.yaw_rad = fmodf(game->player.yaw_rad, 2 * M_PI);
	dir = vec2_from_angle(player->yaw_rad);
	move = vec2_add(vec2_scale(dir, forward), vec2_scale(vec2_new(-dir.y, dir.x), strafe));
	if (strafe == 0 && forward == 0)
	{
		move = player->last_move;
		player->accel = fmaxf(player->accel - player->friction, 0);
	}
	else
		player->accel = fclamp(player->accel + player->accel_speed, 0, player->base_speed + player->accel_max);
	if (move.x != 0 || move.y != 0)
		move = vec2_scale(vec2_normalize(move), player->accel);
	player->last_move = move;
	player_move_collision((t_vec3){move.x, move.y, 0}, player, game);
	fly = (key_check(KEY_TEST_UP, game) - key_check(KEY_TEST_DOWN, game)) * 0.025;
	if (fly == 0)
		player_handle_jump(player, game);
	else
		player_add_z(fly, player);
}
