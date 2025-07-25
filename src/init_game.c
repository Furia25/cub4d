/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/25 20:10:19 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_textures.h"

#include "mlx.h"
#include "mlx_int.h"

#include <string.h>
#include <mlx.h>
#include "glyphs.h"

bool	create_frame_image(t_game *game)
{
	t_img_data	*img;

	game->frame = ft_calloc(1, sizeof(t_img_data));
	if (!game->frame)
		return (false);
	game->frame->img_ptr = mlx_new_image(game->mlx,
		game->w_width, game->w_height);
	if (!game->frame->img_ptr)
		return (false);
	img = game->frame;
	img->width = WINDOW_WIDTH + 2;
	img->height = WINDOW_HEIGHT + 2;
	img->connection = game->mlx;
	img->buffer = mlx_get_data_addr(img->img_ptr, &img->pbits,
		&img->size_line, &img->endian);
	game->z_buffer = malloc(game->w_width * game->w_height);
	if (!game->z_buffer)
		return (false);
	return (true);
}

int	init_textures(t_game *game)
{
	char		*path;
	int			index;
	int			parsed_index;

	index = 1;
	while (index < TEXTURE_MAX_COUNT)
	{
		path = (char *)g_textures_files[index];
		parsed_index = ft_atoi(path);
		if (parsed_index != 0)
			path = game->paths[parsed_index - 1];
		if (!is_file_valid(path))
		{
			if (path)
				printf("WARNING : Texture at path \"%s\" is missing\n", path);
			game->textures[index++] = game->textures[TEXTURE_ERROR];
			continue ;
		}
		game->textures[index] = png_open(path);
		if (!game->textures[index++])
			return (0);
	}
	return (1);
}

int	init_assets(t_game *game)
{
	game->textures[TEXTURE_ERROR]
		= png_open((char *)g_textures_files[TEXTURE_ERROR]);
	if (!game->textures[TEXTURE_ERROR])
		return (0);
	if (!init_textures(game))
		return (0);
	if (!glyph_init(GLYPH_PATH))
		return (0);
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
	player->position.z = player->eye_height + 0.5;
	min = vec3_new(player->position.x - size,
		player->position.y - size, player->position.z);
	max = vec3_new(player->position.x + size,
		player->position.y + size, player->position.z - 0.4);
	player->accel = 0;
	player->bbox = bbox_new(min, max);
	player->is_grounded = true;
}

void	run_game(t_game *game)
{
	game->w_width = WINDOW_WIDTH;
	game->w_height = WINDOW_HEIGHT;
	game->w_halfwidth = WINDOW_WIDTH / 2;
	game->w_halfheight = WINDOW_HEIGHT / 2;
	rng_init(&game->rng, 0xCACA);
	if (!init_assets(game))
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
	game->interaction.count = 0;
	game->interaction.npc_id = -1;
	game->state = MENU;
	
	mlx_mouse_hide(game->mlx, game->win);
	init_player(&game->player);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_released, game);
	mlx_mouse_move(game->mlx, game->win, game->w_halfwidth, game->w_halfheight);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_move, game);
	mlx_hook(game->win, DestroyNotify, 0, exit_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
