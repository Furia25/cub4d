/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:10:34 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/04 11:03:05 by halnuma          ###   ########.fr       */
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

	// ft_putstr_fd("zeub", 2);
	game = param;
	return (remove_keys(key_pressed, game->keys));
}

static bool	add_keys(int keycode, t_key *keys)
{
	int			index;
	// uint64_t	timecode;

	index = 0;
	while (index < KEY_MEMORY)
	{
		if (keys[index].keycode == 0)
		{
			keys[index].keycode = keycode;
			keys[index].time = get_time_ms();
			return (true);
		}
		else if (keys[index].keycode == keycode)
			return (true);
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
