/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:47:18 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/04 11:56:33 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "maths2_easing.h"

void	player_move_collision(t_vec3 move, t_player *player, t_game *game)
{
	t_vec3	temp_v;

	temp_v = vec3_new(move.x, 0, 0);
	if (!tilemap_collision_bbox(temp_v, player->collision_box, game->tilemap))
	{
		player->position.x += move.x;
		player->collision_box.min.x += move.x;
		player->collision_box.max.x += move.x;
	}
	temp_v = vec3_new(0, move.y, 0);
	if (!tilemap_collision_bbox(temp_v, player->collision_box, game->tilemap))
	{
		player->position.y += move.y;
		player->collision_box.min.y += move.y;
		player->collision_box.max.y += move.y;
	}
}

void	player_handle_fly(t_player *plr, float fly)
{
	plr->height += fly;
	plr->collision_box.min.z += fly;
	plr->collision_box.max.z += fly;
}

void	player_handle_jump(t_player *plr, t_game *game)
{
	const float	gravity = -0.015f;
	bool		jumping;

	jumping = is_key_pressed(KEY_JUMP, game);
	if (jumping && plr->is_grounded)
	{
		plr->jump_velocity = plr->jump_force;
		plr->is_grounded = false;
	}
	// if (plr->eye_height > 0.3f)
		plr->jump_velocity += gravity;
	if (!tilemap_collision_bbox((t_vec3){0, 0, plr->jump_velocity}, plr->collision_box, game->tilemap))
	{
		plr->height += plr->jump_velocity;
		plr->collision_box.min.z += plr->jump_velocity;
		plr->collision_box.max.z += plr->jump_velocity;
	}
	else
	{
		plr->jump_velocity = 0.0f;
		plr->is_grounded = true;
	}
}

void	update_player(t_player *player, t_game *game)
{
	float	fly;
	float	forward;
	float	strafe;
	t_vec2	dir;
	t_vec2	move;

	strafe =  is_key_pressed(KEY_RIGHT, game) - is_key_pressed(KEY_LEFT, game);
	forward =  is_key_pressed(KEY_UP, game) - is_key_pressed(KEY_DOWN, game);
	player->rad_direction += (M_PI / 100) * (is_key_pressed(KEY_TEST_RIGHT, game) - is_key_pressed(KEY_TEST_LEFT, game));
	dir = vec2_from_angle(player->rad_direction);
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
	fly = (is_key_pressed(KEY_TEST_UP, game) - is_key_pressed(KEY_TEST_DOWN, game)) * 0.05;
	if (fly == 0)
		player_handle_jump(player, game);
	else
		player_handle_fly(player, fly);
}
