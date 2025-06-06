/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:29:22 by val               #+#    #+#             */
/*   Updated: 2025/06/06 15:34:23 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_key_pressed(t_key_type type, t_game *game)
{
	return (game->key_buffer[type].pressed);
}

void	show_keys(t_game *game)
{
	size_t	index;

	index = 0;
	while (index < KEY_MAX_COUNT)
	{
		if (index == KEY_MAX_COUNT - 1)
			printf("%d", game->key_buffer[index].pressed);
		else
			printf("%d ,", game->key_buffer[index].pressed);
		index++;
	}
	printf("\n");
}

void	handle_keys(t_game *game)
{
	size_t	index;

	index = 0;
	while (index < KEY_MAX_COUNT)
	{
		if (game->key_buffer[index].pressed)
			handle_key(game->key_buffer[index], game);
		index++;
	}
}

void	handle_key(t_key key, t_game *game)
{
	if (key.type == KEY_QUIT)
		exit_game(game);
	if (key.type == KEY_TEST && get_time_ms() - key.time > 50000)
		ft_putstr_fd("TEST\n", 2);
}
