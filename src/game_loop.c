/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:10:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/02 13:46:58 by halnuma          ###   ########.fr       */
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
		ft_memset(frame->buffer, 0, frame->width * frame->height * (frame->pbits / 8));
		handle_keys(game);
		if (is_key_pressed(KEY_PAUSE, game))
			game->state = PAUSED;
		if (game->state == MENU)
			render_start_menu(game);
		else if (game->state == PLAYING)
		{
			update_player(&game->player, game);
			render(game);
		}
		else if (game->state == PAUSED)
			render_pause_menu(game);
		// draw_text(L"»2~Th«Tart »4*«macaroon»*2🌈« RAINBOW»🌈« gummies marshmallow muffin jujubes »🌈«RAINBOW»_1« pie tart bear claw. Tootsie roll sesame »🌈«RAINBOW»🌈« snaps bonbon pie toffee ice cream fruitcake danish. Cake chupa chups sweet roll caramels sweet cotton candy sweet. Bear claw croissant tootsie roll shortbread danish candy powder. Cheesecake tart icing biscuit pudding chocolate bar lollipop croissant tart.", (t_text_properties){0, 100, 0.8, 0, 0, 1, 16, game->start_time}, frame);
		mlx_put_image_to_window(game->mlx, game->win, frame->img_ptr, 0, 0);
		printf("FPS : %lu TIME S :%ld\n", get_fps(time), get_elapsed_ms() / 1000);
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
