/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/06 22:50:56 by vdurand          ###   ########.fr       */
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

const char *test_tab[6] = {
	"11111111",
	"10011101",
	"10001001",
	"10001001",
	"10000001",
	"11111111"
};

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
	game->tilemap = tilemap_from_tab((char **)test_tab, 8, 6, 1);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_released, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	game->player.speed = 0.01;
	if (!create_frame_image(game))
		exit_game(game);
	mlx_loop(game->mlx);
}
