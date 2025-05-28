/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:10:34 by halnuma           #+#    #+#             */
/*   Updated: 2025/05/28 21:11:25 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	add_keys(int keycode, t_key *keys);
static bool	remove_keys(int keycode, t_key *keys);

int	key_pressed(int key_pressed, void *param)
{
	t_game	*game;

	game = param;
	return (add_keys(key_pressed, game->keys));
}

int	key_released(int key_pressed, void *param)
{
	t_game	*game;

	game = param;
	return (remove_keys(key_pressed, game->keys));
}

static bool	add_keys(int keycode, t_key *keys)
{
	int	index;

	index = 0;
	while (index < KEY_MEMORY)
	{
		if (keys[index].keycode == 0)
		{
			keys[index].keycode = keycode;
			keys[index].time = get_time_ms();
			return (true);
		}
		index++;
	}
	return (false);
}

static bool	remove_keys(int keycode, t_key *keys)
{
	int	index;

	index = 0;
	while (index < KEY_MEMORY)
	{
		if (keys[index].keycode == keycode)
		{
			keys[index].keycode = 0;
			keys[index].time = 0;
			return (true);
		}
		index++;
	}
	return (false);
}
