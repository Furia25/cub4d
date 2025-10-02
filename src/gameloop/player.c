/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:47:18 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 12:34:24 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "maths2_easing.h"

static inline void	player_handle_move(t_player *player, t_game *game);
static inline void	player_move_collision(t_vec3 move,
						t_player *player, t_game *game);
static inline void	player_handle_jump(t_player *plr, t_game *game);

void	player_death(t_player *player)
{
	printf(ANSI_BOLD ANSI_RED DEATH_MESSAGE ANSI_RESET);
	object_set_pos(player->spawn_pos, &player->position, &player->bbox);
}

void	update_player(t_player *player, t_game *game)
{
	const bool	gravity_key = key_is_released(KEY_GRAVITY, game);
	const float	fly = key_check(KEY_FLY_UP, game)
		- key_check(KEY_FLY_DOWN, game);

	if (gravity_key)
		player->has_gravity = !player->has_gravity;
	player->yaw_rad += (M_PI / 45)
		* (key_check(KEY_LOOK_RIGHT, game) - key_check(KEY_LOOK_LEFT, game));
	game->player.yaw_rad = fmodf(game->player.yaw_rad, 2 * M_PI);
	player_handle_move(player, game);
	if (fly == 0)
		player_handle_jump(player, game);
	else
		player_add_z(fly * 0.05, player);
	if (player->position.z < -8 && player->has_gravity)
		player_death(player);
}

static inline void	player_handle_move(t_player *player, t_game *game)
{
	const float	forward = key_check(KEY_UP, game) - key_check(KEY_DOWN, game);
	const float	strafe = key_check(KEY_RIGHT, game) - key_check(KEY_LEFT, game);
	t_vec2		move;
	t_vec2		dir;

	dir = vec2_from_angle(player->yaw_rad);
	move = vec2_add(vec2_scale(dir, forward),
			vec2_scale(vec2_new(-dir.y, dir.x), strafe));
	if (strafe == 0 && forward == 0)
	{
		move = player->last_move;
		player->accel = fmaxf(player->accel - player->friction, 0);
	}
	else
		player->accel = fminf(player->accel + player->accel_speed,
				player->base_speed + player->accel_max);
	if (move.x != 0 || move.y != 0)
		move = vec2_scale(vec2_normalize(move), player->accel);
	player->last_move = move;
	if (player->has_gravity)
		player_move_collision((t_vec3){move.x, move.y, 0}, player, game);
	else
		object_move(vec2_to_vec3(move), &player->position, &player->bbox);
}

static inline void	player_move_collision(t_vec3 move,
						t_player *player, t_game *game)
{
	bool	stepped;
	t_vec3	temp_v;
	t_bbox	temp_bbox;

	stepped = false;
	temp_bbox = player->bbox;
	bbox_add((t_vec3){0, 0, PLAYER_STEP_THRESHOLD}, &temp_bbox);
	temp_v = (t_vec3){move.x, 0, 0};
	if (!tilemap_collide_bbox(temp_v, player->bbox, game->tilemap))
		object_move(temp_v, &player->position, &player->bbox);
	else if (!tilemap_collide_bbox(temp_v, temp_bbox, game->tilemap))
	{
		object_move((t_vec3){move.x, 0, PLAYER_STEP_THRESHOLD},
			&player->position, &player->bbox);
		stepped = true;
	}
	temp_v = (t_vec3){0, move.y, 0};
	if (!tilemap_collide_bbox(temp_v, player->bbox, game->tilemap))
		object_move(temp_v, &player->position, &player->bbox);
	else if (!tilemap_collide_bbox(temp_v, temp_bbox, game->tilemap))
		object_move((t_vec3){0, move.y, PLAYER_STEP_THRESHOLD * stepped},
			&player->position, &player->bbox);
}

static inline void	player_handle_jump(t_player *plr, t_game *game)
{
	const float	gravity = -0.013f;
	bool		jumping;

	plr->is_grounded = tilemap_collide_bbox((t_vec3){0, 0, -0.1},
			plr->bbox, game->tilemap);
	jumping = key_check(KEY_JUMP, game);
	if (jumping && plr->is_grounded)
	{
		plr->is_grounded = false;
		plr->jump_velocity = plr->jump_force;
	}
	if (plr->has_gravity)
	{
		if (plr->jump_velocity > -4)
			plr->jump_velocity += gravity;
	}
	else
		plr->jump_velocity = 0;
	if (!tilemap_collide_bbox((t_vec3){0, 0, plr->jump_velocity},
		plr->bbox, game->tilemap))
		player_add_z(plr->jump_velocity, plr);
	else
		plr->jump_velocity = 0.0f;
}
