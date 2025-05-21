/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:21:21 by halnuma           #+#    #+#             */
/*   Updated: 2025/05/21 11:22:58 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game		game;

	if (ac != 2)
	{
		ft_putstr_fd("Error: One argument needed", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_file_extension(av[1]))
	{
		ft_putstr_fd("Error: Wrong file extension (.ber needed)", 2);
		exit(EXIT_FAILURE);
	}
	check_map_errors(&game, av[1]);
	run_game(&game);
	return (0);
}

int	check_file_extension(char *filename)
{
	char	*file_extension;

	file_extension = ft_strchr(filename, '.');
	if (!file_extension)
		return (0);
	if (ft_strncmp(file_extension, ".cub", 5))
		return (0);
	return (1);
}
