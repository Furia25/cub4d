/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:10:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/10 18:21:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "cub3d_entities.h"
#include "glyphs.h"

uint64_t	get_fps(uint64_t start_time);

static inline void	play_loop(t_game *game, t_img_data *frame, uint64_t fps)
{
	if (key_is_pressed(KEY_PAUSE, game))
		game->state = PAUSED;
	entities_tick(game);
	update_anim(&game->water_anim);
	update_player(&game->player, game);
	ft_memset(frame->buffer, 0, frame->width * frame->height * (frame->pbits / 8));
	render(game);
	printf("FPS : %lu TIME S :%ld\n", fps, get_elapsed_ms() / 1000);
}

int	game_loop(void *param)
{
	static uint64_t	last_time = 0;
	uint64_t		time;
	t_game			*game;
	t_img_data		*frame;

	game = param;
	frame = game->frame;
	time = get_time_ms();
	if (time >= last_time)
	{
		last_time = time + 32;
		if (key_check(KEY_QUIT, game))
			exit_game(game);
		if (game->state == MENU || game->state == PAUSED)
			render_menu(game, game->state == MENU);
		else
			play_loop(game, frame, get_fps(time));
		mlx_put_image_to_window(game->mlx, game->win, frame->img_ptr, -2, -2);
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

	if (fps_time == 20)
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
