/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/02 04:35:23 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_textures.h"
#include "cub3d_entities.h"
#include <mlx.h>

void	init_engine_preparsing(t_game *game)
{
	game->entity_manager.entities = vector_new();
	game->entity_manager.entities->val_free = (void (*)(void *))entity_free;
	if (!game->entity_manager.entities)
		throw_error(game, ERROR_LOADING);
	game->events_postload = event_queue_init(game);
}

static inline void	init_player(t_player *player);
static inline bool	create_frame_image(t_game *game);

void	init_engine(t_game *game)
{
	game->win.width = WINDOW_WIDTH;
	game->win.height = WINDOW_HEIGHT;
	game->win.halfwidth = WINDOW_WIDTH / 2;
	game->win.halfheight = WINDOW_HEIGHT / 2;
	game->aspect_res = game->win.width / (float)ASPECT_RES;
	rng_init(&game->rng, get_seed());
	init_assets(game);
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
	event_queue_execute(game->events_postload, game);
	init_player(&game->player);
	mlx_loop(game->mlx);
}

static inline bool	create_frame_image(t_game *game)
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

static inline void	init_player(t_player *player)
{
	float	size;
	t_vec3	min;
	t_vec3	max;

	player->has_gravity = true;
	player->base_speed = 0.05f;
	player->accel_max = 0.04;
	player->accel_speed = 0.003;
	player->friction = 0.0078;
	player->eye_height = 0.3f;
	player->jump_force = 0.15f;
	player->fov_deg = 80;
	size = PLAYER_SIZE / 2;
	player->position.z = player->position.z + player->eye_height + 0.5;
	min = vec3_new(player->position.x - size,
		player->position.y - size, player->position.z);
	max = vec3_new(player->position.x + size,
		player->position.y + size, player->position.z - 0.4);
	player->spawn_pos = player->position;
	player->accel = 0;
	player->bbox = bbox_new(min, max);
	player->is_grounded = true;
}
