/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:29:22 by val               #+#    #+#             */
/*   Updated: 2025/06/05 23:48:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_key_pressed(int keycode, t_game *game)
{
	size_t	index;

	index = 0;
	while (index < KEY_MEMORY)
	{
		if (game->keys[index].keycode == keycode)
			return (true);
		index++;
	}
	return (false);
}

void	handle_keys(t_game *game)
{
	size_t	index;

	index = 0;
	while (index < KEY_MEMORY)
	{
		handle_key(game->keys[index], game);
		index++;
	}
}

void	handle_key(t_key key, t_game *game)
{
	if (key.keycode == KEY_QUIT)
		exit_game(game);
	if (key.keycode == KEY_TEST && get_time_ms() - key.time > 50000)
		ft_putstr_fd("TEST\n", 2);
}
