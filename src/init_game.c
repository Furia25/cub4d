/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/04 17:44:14 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include <mlx.h>
#include "glyphs.h"

bool	create_frame_image(t_game *game)
{
	t_img_data	*img;

	game->img = ft_calloc(1, sizeof(t_img_data));
	if (!game->img)
		return (false);
	game->img->img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img->img_ptr)
		return (false);
	img = game->img;
	img->width = WINDOW_WIDTH + 2;
	img->height = WINDOW_HEIGHT + 2;
	img->connection = game->mlx;
	img->buffer = mlx_get_data_addr(img->img_ptr, &img->pbits, &img->size_line, &img->endian);
	return (true);
}

int	init_textures(t_game *game)
{
	game->textures[TEXTURE_NORTH] = png_open(game->paths[0]);
	if (!game->textures[TEXTURE_NORTH])
		return (0);
	game->textures[TEXTURE_EAST] = png_open(game->paths[3]);
	if (!game->textures[TEXTURE_EAST])
		return (0);
	game->textures[TEXTURE_WEST] = png_open(game->paths[2]);
	if (!game->textures[TEXTURE_WEST])
		return (0);
	game->textures[TEXTURE_SOUTH] = png_open(game->paths[1]);
	if (!game->textures[TEXTURE_SOUTH])
		return (0);
	game->textures[TEXTURE_TOP] = png_open("assets/textures/wall_top.png");
	if (!game->textures[TEXTURE_TOP])
		return (0);
	game->textures[TEXTURE_BOT] = png_open("assets/textures/wall_bot.png");
	if (!game->textures[TEXTURE_BOT])
		return (0);
	if (!glyph_init("assets/textures/glyph.png"))
		return (0);
	return (1);
}

int	init_assets(t_game *game)
{
	if (!init_textures(game))
		return (0);
	return (1);
}

int	init_menu(t_game *game)
{
	game->menu.assets[ASSET_BG_START] = png_open("assets/menu/bg_start.png");
	if (!game->menu.assets[ASSET_BG_START])
		return (0);
	game->menu.assets[ASSET_BG_PAUSE] = png_open("assets/menu/bg_pause.png");
	if (!game->menu.assets[ASSET_BG_PAUSE])
		return (0);
	game->menu.assets[ASSET_SELECTOR] = png_open("assets/menu/selector.png");
	if (!game->menu.assets[ASSET_SELECTOR])
		return (0);
	game->menu.action = 0;
	return (1);
}

void	init_player(t_player *player)
{
	float	size;
	t_vec3	min;
	t_vec3	max;

	player->base_speed = 0.07f;
	player->accel_max = 0.03;
	player->accel_speed = 0.003;
	player->friction = 0.008;
	player->air_friction = 0.0005;
	player->eye_height = 0.3f;
	player->jump_force = 0.3f;
	player->fov_deg = 80;
	size = PLAYER_SIZE / 2;
	player->height = player->eye_height + 0.4;
	min = vec3_new(player->position.x - size, player->position.y - size, 0);
	min.z = player->eye_height;
	max = vec3_new(player->position.x + size, player->position.y + size, 0);
	max.z = 0.1f;
	player->accel = 0;
	player->collision_box = bbox_new(min, max);
	player->is_grounded = true;
}

void	run_game(t_game *game)
{
	rng_init(&game->rng, 0xCACA);
	if (!init_assets(game))
		exit_game(game);
	if (!init_menu(game))
		exit_game(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error while loading mlx", 2);
		exit_game(game);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!game->win)
	{
		ft_putstr_fd("Error while loading window", 2);
		exit_game(game);
	}
	if (!create_frame_image(game))
		exit_game(game);
	game->start_time = time_init();
	game->interaction = 0;
	game->state = MENU;
	mlx_mouse_hide(game->mlx, game->win);
	init_player(&game->player);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_released, game);
	mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_move, game);
	mlx_hook(game->win, DestroyNotify, 0, exit_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
