/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:09:37 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/04 16:07:15 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_game *game)
{
	free_map(game->file_content);
	free(game->paths);
	free(game->colors);
	free(game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	// destroy_images(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
