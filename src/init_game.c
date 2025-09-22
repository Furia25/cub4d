/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/22 18:59:38 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_textures.h"
#include "cub3d_entities.h"

#include <mlx.h>
#include "glyphs.h"
#include <errno.h>

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
	game->z_buffer = malloc((game->win.width * game->win.height + 8) * sizeof(float));
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
		if (path != NULL)
		{
			parsed_index = ft_atoi(path);
			if (parsed_index != 0)
				path = game->parsing.paths[parsed_index - 1];
			errno = 0;
			if (path != NULL)
				game->textures[index] = png_open(path);
			if (!game->textures[index])
			{
				game->textures[index] = game->textures[TEXTURE_ERROR];
				printf(WARNING_TEXTURE, path);
			}
		}
		index++;
	}
	return (1);
}

int	init_assets(t_game *game)
{
	game->textures[TEXTURE_ERROR]
		= png_open((char *)g_textures_files[TEXTURE_ERROR]);
	if (!game->textures[TEXTURE_ERROR])
		throw_error(game, ERROR_LOADING_ASSETS);
	if (!init_textures(game))
		throw_error(game, ERROR_LOADING_ASSETS);
	if (!glyph_init(GLYPH_PATH))
		throw_error(game, ERROR_LOADING_ASSETS);
	game->cigarette.sheet.asset = game->textures[TEXTURE_CIGARETTE];
	game->cigarette.sheet.width = 287;
	game->cigarette.sheet.height = 357;
	game->cigarette.sheet.spr_per_line = 19;
	game->cigarette.transform.x = 0;
	game->cigarette.transform.y = -400;
	game->cigarette.transform.depth = 0;
	game->cigarette.transform.width = 538 * 2;
	game->cigarette.transform.height = 673 * 2;
	game->cigarette.transform.color = g_colors[C_WHITE];
	game->cigarette.transform.scale = 1.25;
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

void	init_water(t_animated_tiles *water_anim, t_game *game)
{
	water_anim->type = TEXTURE_WATER;
	water_anim->frames_num = 20;
	water_anim->frame_time = 0.5;
	water_anim->actual_frame = 0;
	water_anim->frames[0] = game->textures[TEXTURE_WATER0];
	water_anim->frames[1] = game->textures[TEXTURE_WATER1];
	water_anim->frames[2] = game->textures[TEXTURE_WATER2];
	water_anim->frames[3] = game->textures[TEXTURE_WATER3];
	water_anim->frames[4] = game->textures[TEXTURE_WATER4];
	water_anim->frames[5] = game->textures[TEXTURE_WATER5];
	water_anim->frames[6] = game->textures[TEXTURE_WATER6];
	water_anim->frames[7] = game->textures[TEXTURE_WATER7];
	water_anim->frames[8] = game->textures[TEXTURE_WATER8];
	water_anim->frames[9] = game->textures[TEXTURE_WATER9];
	water_anim->frames[10] = game->textures[TEXTURE_WATER10];
	water_anim->frames[11] = game->textures[TEXTURE_WATER11];
	water_anim->frames[12] = game->textures[TEXTURE_WATER12];
	water_anim->frames[13] = game->textures[TEXTURE_WATER13];
	water_anim->frames[14] = game->textures[TEXTURE_WATER14];
	water_anim->frames[15] = game->textures[TEXTURE_WATER15];
	water_anim->frames[16] = game->textures[TEXTURE_WATER16];
	water_anim->frames[17] = game->textures[TEXTURE_WATER17];
	water_anim->frames[18] = game->textures[TEXTURE_WATER18];
	water_anim->frames[19] = game->textures[TEXTURE_WATER19];
}

void	color_texture(t_png *tex, t_rgba8 tint)
{
	size_t	x;
	size_t	y;
	t_rgba8	*pixel;

	if (tint.channels.r == 255 && tint.channels.g == 255 && tint.channels.b == 255)
		return ;
	y = 0;
	while (y < tex->header.height)
	{
		x = 0;
		while (x < tex->header.width)
		{
			pixel = (t_rgba8 *)&tex->pixels_8bit[y * tex->header.width + x];
			pixel->channels.r = lerp(pixel->channels.r, tint.channels.r, 0.4);
			pixel->channels.g = lerp(pixel->channels.g, tint.channels.g, 0.4);
			pixel->channels.b = lerp(pixel->channels.b, tint.channels.b, 0.4);
			x++;
		}
		y++;
	}
}

#define print_color(rgb)	printf(#rgb " %d, %d, %d\n", rgb.channels.r, rgb.channels.g, rgb.channels.b);

void	run_game(t_game *game)
{
	game->win.width = WINDOW_WIDTH;
	game->win.height = WINDOW_HEIGHT;
	game->win.halfwidth = WINDOW_WIDTH / 2;
	game->win.halfheight = WINDOW_HEIGHT / 2;
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
	game->start_time = time_init();
	game->state = MENU;
	mlx_mouse_hide(game->mlx, game->win.ptr);
	init_player(&game->player);
	t_vec3	pos;
	t_vec3	ppos;
	ppos = game->player.position;
	for (int i = 0; i < 10000; i++)
	{
		pos = ppos;
		pos.x += rng_float_range(&game->rng, -100, 100);
		pos.y += rng_float_range(&game->rng, -100, 100);
		pos.z += rng_float_range(&game->rng, 0, 100);
		entity_add(entity_new_example(pos, game), game);
	}
	init_hooks(game);
	init_water(&game->water_anim, game);
	color_texture(game->textures[TEXTURE_GRASS], game->parsing.f_color);
	mlx_loop(game->mlx);
}
