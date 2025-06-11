/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/11 19:16:21 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <stdlib.h>
#include <string.h>
#include <mlx.h>

#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <stdlib.h>
#include <string.h>
#include <mlx.h>

#include <X11/Xlib.h>
#include <X11/cursorfont.h>

/* int mouse_hide(t_xvar *xvar, t_win_list *win, Cursor *cursor)
{
	const static char	empty_data[] = {45};
	Pixmap		blank;
	XColor		dummy;
		
	blank = XCreateBitmapFromData(xvar->display, win->window, empty_data, 1, 1);
	if (blank == 0)
		return (0);
	memset(&dummy, 0, sizeof(XColor));
	*cursor = XCreatePixmapCursor(xvar->display, blank, blank, &dummy, &dummy, 0, 0);
	XFreePixmap(xvar->display, blank);
	if (*cursor == 0)
		return (0);
	XDefineCursor(xvar->display, win->window, *cursor);
	return (1); */
}

bool	create_frame_image(t_game *game)
{
	t_img_data	*img;

	game->img = ft_calloc(1, sizeof(t_img_data));
	if (!game->img)
		return (false);
	game->img->img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img->img_ptr)
		return (false);
	img = game->img;
	img->width = WINDOW_WIDTH;
	img->height = WINDOW_HEIGHT;
	img->connection = game->mlx;
	img->buffer = mlx_get_data_addr(img->img_ptr, &img->pbits, &img->size_line, &img->endian);
	return (true);
}

void	init_player(t_player *player)
{
	float	size;
	t_vec3	min;
	t_vec3	max;

	player->fov_deg = 80;
	size = PLAYER_SIZE / 2;
	player->speed = 0.07;
	min = vec3_new(player->position.x - size, player->position.y - size, 0);
	max = vec3_new(player->position.x + size, player->position.y + size, 0);
	player->collision_box = bbox_new(min, max);
}

void	run_game(t_game *game)
{
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
	mouse_hide(game->mlx, game->win, &game->cursor);
	init_player(&game->player);
	draw_minimap(game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_released, game);
	mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_move, game);
	mlx_hook(game->win, DestroyNotify, 0, exit_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
