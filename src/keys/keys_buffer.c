/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:10:34 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/04 17:56:00 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int key_pressed, void *param)
{
	t_game	*game;
	int		index;

	game = param;
	index = 0;
	while (index < KEY_MAX_COUNT)
	{
		if (g_keymap[index] == key_pressed)
		{
			game->key_buffer[index].type = index;
			game->key_buffer[index].pressed = true;
			game->key_buffer[index].time = get_time_ms();
			game->key_buffer[index].pressed_once = true;
			game->key_buffer[index].released_once = false;
			return (true);
		}
		index++;
	}
	return (false);
}

int	key_released(int key_pressed, void *param)
{
	t_game	*game;
	int		index;

	game = param;
	index = 0;
	while (index < KEY_MAX_COUNT)
	{
		if (g_keymap[index] == key_pressed)
		{
			game->key_buffer[index].pressed = false;
			game->key_buffer[index].time = 0;
			game->key_buffer[index].pressed_once = false;
			game->key_buffer[index].released_once = true;
			return (true);
		}
		index++;
	}
	return (false);
}
