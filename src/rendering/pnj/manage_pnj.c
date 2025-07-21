/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pnj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:48:51 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/21 10:47:14 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	tablen(char **text)
{
	int	i;

	i = 0;
	while (text[i])
		i++;
	return (i);
}

static void	display_interaction(t_game *game, char **text)
{
	static uint64_t	time;
	t_button		btn;

	if (key_is_released(KEY_INTERACT, game))
	{
		game->interaction.count++;
		time = get_time_ms();
	}
	if (!game->interaction.count)
	{
		btn.x = ((WINDOW_WIDTH / 2) - (S_BUTTON_INTERACT / 2));
		btn.y = ((WINDOW_HEIGHT / 2) - (S_BUTTON_INTERACT / 2));
		btn.width = S_BUTTON_INTERACT;
		btn.height = S_BUTTON_INTERACT;
		draw_interact_button(game, &btn, 0);
	}
	else if (game->interaction.count - 1 < tablen(text))
		draw_textbox(game, text[game->interaction.count - 1], time);
	else if (game->interaction.count - 1 >= tablen(text))
		game->interaction.count = 0;
}

static int	is_pnj_in_range(t_vec3 player_pos, t_vec3 pnj_pos)
{
	float	dist;

	dist = vec3_distance(player_pos, pnj_pos);
	if (dist < INTERACTION_RANGE)
		return (1);
	return (0);
}

static void	manage_interaction(t_game *game, int i, int *pnj_in_range)
{
	if (is_pnj_in_range(game->player.position, \
		game->pnjs[game->interaction.pnj_id].position))
		display_interaction(game, \
			game->pnjs[game->interaction.pnj_id].text);
	else
	{
		game->interaction.count = 0;
		game->interaction.pnj_id = i;
		display_interaction(game, game->pnjs[i].text);
	}
	*pnj_in_range = 1;
}

void	manage_pnjs(t_game *game)
{
	int		i;
	float	dist;
	int		pnj_in_range;

	i = 0;
	pnj_in_range = 0;
	while (i < game->pnj_count)
	{
		dist = vec3_distance(game->player.position, game->pnjs[i].position);
		if (dist < INTERACTION_RANGE)
			manage_interaction(game, i, &pnj_in_range);
		i++;
	}
	if (!pnj_in_range)
	{
		game->interaction.pnj_id = -1;
		game->interaction.count = 0;
	}
}
