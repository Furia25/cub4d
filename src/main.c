/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:21:21 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/09 14:48:40 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game		game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
	{
		ft_putstr_fd("Error: One argument needed", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_file_extension(av[1]))
	{
		ft_putstr_fd("Error: Wrong file extension (.cub needed)", 2);
		exit(EXIT_FAILURE);
	}
	check_map_errors(&game, av[1]);
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
