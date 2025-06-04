/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:29:22 by val               #+#    #+#             */
/*   Updated: 2025/06/04 16:13:05 by halnuma          ###   ########.fr       */
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

char	test_next_tile(t_game *game, int key_pressed)
{
	double	test_x;
	double	test_y;

	test_y = game->pos_y;
	test_x = game->pos_x;
	if (key_pressed == KEY_UP)
		test_y -= 0.125;
	if (key_pressed == KEY_LEFT)
		test_x -= 0.125;
	if (key_pressed == KEY_RIGHT)
		test_x += 0.125 + (double)1 / MINIMAP_P_SIZE;
	if (key_pressed == KEY_DOWN)
		test_y += 0.125 + (double)1 / MINIMAP_P_SIZE;
	if (game->map[(int)test_y][(int)test_x] == '1')
		return ('1');
	else
		return ('0');
}

void	handle_dir_input(t_game *game, double pos_x, double pos_y, int key_pressed)
{
	char	next_tile;

	next_tile = test_next_tile(game, key_pressed);
	if (next_tile == '0')
	{
		game->pos_x = pos_x;
		game->pos_y = pos_y;
		draw_minimap(game);
	}
}

int	key_hook(int key_pressed, void *param)
{
	t_game	*game;

	game = param;
	(void)key_pressed;
	if (key_pressed == KEY_QUIT)
		exit_game(game);
	// if (key_pressed == KEY_TEST && get_time_ms() - key.time > 50000)
	// 	ft_putstr_fd("TEST\n", 2);
	if (key_pressed == KEY_UP)
		handle_dir_input(game, game->pos_x, (game->pos_y - 0.125), key_pressed);
	if (key_pressed == KEY_RIGHT)
		handle_dir_input(game, (game->pos_x + 0.125), game->pos_y, key_pressed);
	if (key_pressed == KEY_DOWN)
		handle_dir_input(game, game->pos_x, (game->pos_y + 0.125), key_pressed);
	if (key_pressed == KEY_LEFT)
		handle_dir_input(game, (game->pos_x - 0.125), game->pos_y, key_pressed);
	return (1);
}

void	handle_key(t_key key, t_game *game)
{
	if (key.keycode == KEY_QUIT)
		exit_game(game);
	if (key.keycode == KEY_TEST && get_time_ms() - key.time > 50000)
		ft_putstr_fd("TEST\n", 2);
	if (key.keycode == KEY_UP)
		handle_dir_input(game, game->pos_x, (game->pos_y - 0.125), key.keycode);
	if (key.keycode == KEY_RIGHT)
		handle_dir_input(game, (game->pos_x + 0.125), game->pos_y, key.keycode);
	if (key.keycode == KEY_DOWN)
		handle_dir_input(game, game->pos_x, (game->pos_y + 0.125), key.keycode);
	if (key.keycode == KEY_LEFT)
		handle_dir_input(game, (game->pos_x - 0.125), game->pos_y, key.keycode);
}
