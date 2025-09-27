/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:21:21 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/27 16:33:03 by vdurand          ###   ########.fr       */
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
	parsing(av[1], &game);
	throw_error(&game, ERROR_WTF);
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
		return (0);
	return (1);
}
