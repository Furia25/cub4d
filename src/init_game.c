/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:25:01 by halnuma           #+#    #+#             */
/*   Updated: 2025/05/28 21:09:35 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"

int	loop(void *param)
{
	t_game	*game;
	size_t	index;

	index = 0;
	game = param;
	while (index < KEY_MEMORY)
	{
		printf("{%d} ", game->keys[index].keycode);
		index++;
	}
	printf("\n");
	usleep(100000);
	return (1);
}

void	run_game(t_game *game)
{
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
	mlx_hook(game->win, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->win, KeyPress, KeyReleaseMask, key_released, game);
	mlx_hook(game->win, DestroyNotify, 0, exit_game, game);
	mlx_loop_hook(game->mlx, loop, game);
	mlx_loop(game->mlx);
}
