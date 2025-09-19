/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:21:21 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/19 16:21:27 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game		game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
	{
		ft_putstr_fd("Error: One argument needed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_file_extension(av[1]))
	{
		ft_putstr_fd("Error: Wrong file extension (.cub needed)\n", 2);
		exit(EXIT_FAILURE);
	}
	parsing(&game, av[1]);
	game.tilemap = tilemap_from_tab(game.parsing.map, game.parsing.map_width, game.parsing.map_height, 1);
	if (!game.parsing.colors)
		exit_game(&game);
	run_game(&game);
	return (0);
}

int	check_file_extension(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	while (filename[i] != '.')
		i--;
	if (ft_strncmp(&filename[i], ".cub", 5))
		return (0);
	return (1);
}
