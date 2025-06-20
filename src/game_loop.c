/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:10:04 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/20 09:33:46 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_rendering.h"
#include "mlx.h"
#include "mlx_int.h"

int	game_loop(void *param)
{
	t_game			*game;
	t_img_data		*frame;

	game = param;
	frame = game->img;
	memset(frame->buffer, 0, frame->width * frame->height * (frame->pbits / 8));
	handle_keys(game);
	update_player(&game->player, game);
	render(game);
	mlx_put_image_to_window(game->mlx, game->win, frame->img_ptr, 0, 0);
	return (1);
}
