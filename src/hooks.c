/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:16:45 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/02 15:42:52 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mouse_move(int x, int y, t_game *game);

//mlx_mouse_hide(game->mlx, game->win.ptr);

void	init_hooks(t_game *game)
{
	mlx_hook(game->win.ptr, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win.ptr, KeyRelease, KeyReleaseMask, key_released, game);
	mlx_hook(game->win.ptr, MotionNotify, PointerMotionMask, mouse_move, game);
	mlx_hook(game->win.ptr, DestroyNotify, 0, exit_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

static int	mouse_move(int x, int y, t_game *game)
{
	double		x_dif;
	double		y_dif;
	static int	last_x = 0;
	static int	last_y = 0;

	if (game->state != STATE_PLAYING)
		return (1);
	if (last_x == x && last_y == y)
		return (1);
	last_x = x;
	x_dif = (x - game->win.halfwidth) * MOUSE_SENS;
	last_y = y;
	y_dif = -(y - game->win.halfheight);
	game->player.yaw_rad += x_dif;
	game->player.yaw_rad = fmodf(game->player.yaw_rad, 2 * M_PI);
	game->player.pitch_offset += y_dif;
	game->player.pitch_offset = clamp(game->player.pitch_offset,
			-game->win.halfheight, game->win.halfheight);
	mlx_mouse_move(game->mlx, game->win.ptr,
		game->win.halfwidth, game->win.halfheight);
	return (1);
}
