/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:09:30 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/09 15:13:52 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rad_to_vect(t_vec2 *direction, float rad)
{
	direction->x = cos(rad);
	direction->y = sin(rad);
}

int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x < WINDOW_WIDTH / 2)
	{
		game->player.rad_direction += MOUSE_SENS * M_PI;
		if (game->player.rad_direction > 2 * M_PI)
			game->player.rad_direction -= 2 * M_PI;
	}
	if (x > WINDOW_WIDTH / 2)
	{
		game->player.rad_direction -= MOUSE_SENS * M_PI;
		if (game->player.rad_direction < -2 * M_PI)
			game->player.rad_direction += 2 * M_PI;
	}
	rad_to_vect(&game->player.direction, game->player.rad_direction);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img_ptr, 0, 0);
	mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	return (0);
}
