/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:47:18 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/16 19:14:12 by vdurand          ###   ########.fr       */
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
	float	forward;
	float	strafe;
	t_vec2	dir;
	t_vec2	move;

	player_handle_jump(player, game);
	strafe =  is_key_pressed(KEY_RIGHT, game) - is_key_pressed(KEY_LEFT, game);
	forward =  is_key_pressed(KEY_UP, game) - is_key_pressed(KEY_DOWN, game);
	player->rad_direction += (M_PI / 100) * (is_key_pressed(KEY_TEST_RIGHT, game) - is_key_pressed(KEY_TEST_LEFT, game));
	dir = vec2_from_angle(player->rad_direction);
	move = vec2_add(vec2_scale(dir, forward), vec2_scale(vec2_new(-dir.y, dir.x), strafe));
	if (vec2_length(move) > 0.0f)
		move = vec2_scale(vec2_normalize(move), player->speed);
	player_move_collision((t_vec3){move.x, move.y, 0}, player, game);
}
