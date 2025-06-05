/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/05 21:41:13 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

int	loop(void *param)
{
	t_game	*game;

	game = param;
	// while (index < KEY_MEMORY)
	// {
	// 	// printf("{%d %lu} \n", game->keys[index].keycode, game->keys[index].time);
	// 	index++;
	// }
	// printf("\n");
	handle_keys(game);
	return (1);
}

void	run_game(t_game *game)
{
	t_win_img	img;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error while loading mlx", 2);
		free_map(game->map);
		exit(EXIT_FAILURE);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!game->win)
	{
		ft_putstr_fd("Error while loading window", 2);
		free_map(game->map);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(EXIT_FAILURE);
	}
	img.img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_line, &img.endian);
	game->img = &img;
	draw_minimap(game);
	// mlx_hook(game->win, KeyPress, KeyPressMask, key_pressed, game);
	// mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_released, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_hook, game);
	mlx_hook(game->win, DestroyNotify, 0, exit_game, game);
	mlx_loop_hook(game->mlx, loop, game);
	mlx_loop(game->mlx);
}
