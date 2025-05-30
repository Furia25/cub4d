/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: val <val@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:29:22 by val               #+#    #+#             */
/*   Updated: 2025/05/29 00:01:14 by val              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
