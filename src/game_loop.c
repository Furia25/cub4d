/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:10:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/25 02:15:01 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "mlx.h"
#include "mlx_int.h"
#include "glyphs.h"

uint64_t	get_fps(uint64_t start_time);

int	game_loop(void *param)
{
	static uint64_t	last_time = 0;
	uint64_t		time;
	t_game			*game;
	t_img_data		*frame;

	game = param;
	frame = game->img;
	time = get_time_ms();
	if (time >= last_time)
	{
		last_time = time + 16;
		memset(frame->buffer, 0, frame->width * frame->height * (frame->pbits / 8));
		handle_keys(game);
		update_player(&game->player, game);
		render(game);
		draw_text(L"»3u«Hello world, My name is cub3d this is my glyph feature! Amazing",
			(t_text_properties){20, 80, 0.7, 0, 0, 0.7, 35}, frame);
		draw_text(L"»5r«CUB3D",
			(t_text_properties){20, 40, 0.8, 0, 0, 0.7, 16}, frame);
		mlx_put_image_to_window(game->mlx, game->win, frame->img_ptr, 0, 0);
		printf("FPS : %lu\n", get_fps(time));
		
	}
	return (1);
}

uint64_t	get_fps(uint64_t start_time)
{
	static int		fps_time = 0;
	static uint64_t fps_total = 0;
	static uint64_t	last = 0;
	uint64_t		actual;
	uint64_t		delta;

	if (fps_time == 10)
	{
		fps_total = 0;
		fps_time = 0;
	}
	delta = get_time_ms() - start_time;
	if (delta == 0)
		delta = 1;
	actual = 1000 / delta;
	if (actual < last)
	{
		fps_total = actual;
		fps_time = 1;
	}
	fps_total += actual;
	fps_time += 1;
	return (fps_total / fps_time); 
}
