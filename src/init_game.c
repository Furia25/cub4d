/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/30 19:17:26 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_textures.h"
#include "cub3d_entities.h"
#include <mlx.h>

bool	create_frame_image(t_game *game)
{
	t_img_data	*img;

	game->frame = ft_calloc(1, sizeof(t_img_data));
	if (!game->frame)
		return (false);
	game->frame->img_ptr = mlx_new_image(game->mlx,
		game->win.width, game->win.height);
	if (!game->frame->img_ptr)
		return (false);
	img = game->frame;
	img->width = WINDOW_WIDTH + 2;
	img->height = WINDOW_HEIGHT + 2;
	img->connection = game->mlx;
	img->buffer = mlx_get_data_addr(img->img_ptr, &img->pbits,
		&img->size_line, &img->endian);
	game->z_buffer = malloc((game->win.width * game->win.height + 8)
		* sizeof(float));
	if (!game->z_buffer)
		return (false);
	return (true);
}

void	init_player(t_player *player)
{
	float	size;
	t_vec3	min;
	t_vec3	max;

	player->has_gravity = true;
	player->base_speed = 0.07f;
	player->accel_max = 0.03;
	player->accel_speed = 0.003;
	player->friction = 0.0075;
	player->air_friction = 0.0005;
	player->eye_height = 0.3f;
	player->jump_force = 0.3f;
	player->fov_deg = 80;
	size = PLAYER_SIZE / 2;
	player->position.z = player->eye_height + 0.5;
	min = vec3_new(player->position.x - size,
		player->position.y - size, player->position.z);
	max = vec3_new(player->position.x + size,
		player->position.y + size, player->position.z - 0.4);
	player->accel = 0;
	player->bbox = bbox_new(min, max);
	player->is_grounded = true;
}

static inline void	spawn_test_entities(t_game *game)
{
	t_vec3	pos;
	t_vec3	ppos;
	int		i;

	i = 1000;
	ppos = game->player.position;
	while (i >= 0)
	{
		pos = ppos;
		pos.x += rng_float_range(&game->rng, -100, 100);
		pos.y += rng_float_range(&game->rng, -100, 100);
		pos.z += rng_float_range(&game->rng, 0, 100);
		entity_add(entity_new_npc(pos, game), game);
		i--;
	}
}
//TEMP

void	init_game(t_game *game)
{
	game->start_time = time_init();
	init_player(&game->player);
	spawn_test_entities(game);
	game->hud_cigarette.actual_anim = &game->hud_cigarette.anim_start;
}

void	init_engine(t_game *game)
{
	game->win.width = WINDOW_WIDTH;
	game->win.height = WINDOW_HEIGHT;
	game->win.halfwidth = WINDOW_WIDTH / 2;
	game->win.halfheight = WINDOW_HEIGHT / 2;
	game->aspect_res = game->win.width / (float)ASPECT_RES;
	rng_init(&game->rng, get_seed());
	init_assets(game);
	game->entity_manager.entities = vector_new();
	game->entity_manager.entities->val_free = (void (*)(void *))entity_free;
	if (!game->entity_manager.entities)
		throw_error(game, ERROR_LOADING);
	game->mlx = mlx_init();
	if (!game->mlx)
		throw_error(game, ERROR_LOADING_GRAPHICS);
	game->win.ptr = mlx_new_window(game->mlx, WINDOW_WIDTH,
		WINDOW_HEIGHT, GAME_NAME);
	if (!game->win.ptr)
		throw_error(game, ERROR_WINDOW);
	if (!create_frame_image(game))
		throw_error(game, ERROR_WINDOW);
	game->state = STATE_MENU;
	init_hooks(game);
	if (game->level_broadcast)
		printf(ANSI_CARRIAGE "%s\n" ANSI_RESET, game->level_broadcast);
	mlx_loop(game->mlx);
}
