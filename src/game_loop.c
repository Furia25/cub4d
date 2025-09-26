/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:10:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/26 02:28:04 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "cub3d_entities.h"
#include "glyphs.h"

uint64_t	get_fps(uint64_t start_time);

static inline void	play_loop(t_game *game, t_img_data *frame, uint64_t time)
{
	uint64_t	fps;

	if (key_is_pressed(KEY_PAUSE, game))
		game->state = STATE_PAUSED;
	entities_tick(game);
	anim_tile_update(&game->water_anim, game);
	update_player(&game->player, game);
	ft_memset(frame->buffer, 0, frame->width * frame->height * (frame->pbits / 8));
	render(game);
	anim_index_update(&game->hud_cigarette.anim_idle_on);
	fps = get_fps(time);
	if (fps != 0)
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
		last_time = time + GAME_INTERVAL_MIN;
		if (key_check(KEY_QUIT, game))
			exit_game(game);
		if (game->state == STATE_MENU || game->state == STATE_PAUSED)
			render_menu(game, game->state == STATE_MENU);
		else
		{
			play_loop(game, frame, time);
		}
		mlx_put_image_to_window(game->mlx, game->win.ptr, frame->img_ptr, -2, -2);
	}
	return (1);
}
