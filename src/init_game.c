/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/06 00:13:45 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

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

void	update_player(t_player *player, t_game *game)
{
	int	x_axis;
	int	y_axis;

	x_axis =  is_key_pressed(KEY_RIGHT, game) - is_key_pressed(KEY_LEFT, game);
	y_axis =  is_key_pressed(KEY_DOWN, game) - is_key_pressed(KEY_UP, game);
	printf("Player : %f, %f\n", player->position.x, player->position.y);
	player->position.x += (x_axis * player->speed);
	player->position.y += (y_axis * player->speed);
}

int	loop(void *param)
{
	t_game	*game;
	t_img_data *frame;

	game = param;
	frame = game->img;
	memset(frame->buffer, 0, frame->width * frame->height * (frame->pbits / 8));
	handle_keys(game);
	update_player(&game->player, game);
	/*TEST TILES*/
	img_draw_rect(rgba8(255, 255, 0, 255), rect_new(game->player.position, vec2_new(50, 50)), frame);
	mlx_put_image_to_window(game->mlx, game->win, frame->img_ptr, 0, 0);
	return (1);
}

void	run_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error while loading mlx", 2);
		exit(EXIT_FAILURE);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!game->win)
	{
		ft_putstr_fd("Error while loading window", 2);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_hook(game->win, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_released, game);
	mlx_loop_hook(game->mlx, loop, game);
	game->player.speed = 3;
	if (!create_frame_image(game))
		exit_game(game);
	mlx_loop(game->mlx);
}
