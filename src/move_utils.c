/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:30 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/20 15:30:54 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rad_to_vect(t_vec2 *direction, float rad)
{
	direction->x = cos(rad);
	direction->y = sin(rad);
}

/* int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x > WINDOW_WIDTH / 2)
	{
		game->player.rad_direction -= MOUSE_SENS * M_PI;
		if (game->player.rad_direction > 2 * M_PI)
			game->player.rad_direction -= 2 * M_PI;
	}
	if (x < WINDOW_WIDTH / 2)
	{
		game->player.rad_direction += MOUSE_SENS * M_PI;
		if (game->player.rad_direction < -2 * M_PI)
			game->player.rad_direction += 2 * M_PI;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
	return (0);
} */

int mouse_move(int x, int y, t_game *game)
{
	double		width;
	double		x_dif;
	static int	last_x = 0;

	(void) y;
	if (last_x == x)
		return (1);
	last_x = x;
	width = WINDOW_WIDTH * 0.5;
	x_dif = (x - width) * MOUSE_SENS;
	game->player.rad_direction += x_dif;
	mlx_mouse_move(game->mlx, game->win, width, WINDOW_HEIGHT / 2);
	return (1);
}

	if (x != WINDOW_WIDTH / 2 || y != WINDOW_HEIGHT / 2)
		mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	return (1);
}
