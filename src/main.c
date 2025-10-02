/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:21:21 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/02 14:27:49 by halnuma          ###   ########.fr       */
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
	if (check_file_extension(av[1]))
	{
		ft_putstr_fd("Error: Wrong file extension (.cub needed)\n", 2);
		exit(EXIT_FAILURE);
	}
	init_engine_preparsing(&game);
	parsing(av[1], &game);
	init_engine(&game);
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
		return (1);
	return (0);
}
