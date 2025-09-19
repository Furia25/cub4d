/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:48:51 by halnuma           #+#    #+#             */
/*   Updated: 2025/09/19 17:01:37 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*static void	display_interaction(t_game *game, char **text)
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
		btn.x = (game->win.halfwidth - (S_BUTTON_INTERACT / 2));
		btn.y = (game->win.height * 0.90 - (S_BUTTON_INTERACT / 2));
		btn.width = S_BUTTON_INTERACT;
		btn.height = S_BUTTON_INTERACT;
		draw_interact_button(game, &btn, 0);
	}
	else if (game->interaction.count - 1 < tablen(text))
		draw_textbox(game, text[game->interaction.count - 1], time);
	else if (game->interaction.count - 1 >= tablen(text))
		game->interaction.count = 0;
}*/

/*static int	is_npc_in_range(t_vec3 player_pos, t_vec3 npc_pos)
{
	float	dist;

	dist = vec3_distance(player_pos, npc_pos);
	if (dist < INTERACTION_RANGE)
		return (1);
	return (0);
}*/

/*static void	manage_interaction(t_game *game, int i, int *npc_in_range)
{
	if (is_npc_in_range(game->player.position, \
		game->npcs[game->interaction.npc_id].position))
		display_interaction(game, \
			game->npcs[game->interaction.npc_id].text);
	else
	{
		game->interaction.count = 0;
		game->interaction.npc_id = i;
		display_interaction(game, game->npcs[i].text);
	}
	*npc_in_range = 1;
}*/

/*void	manage_npcs(t_game *game)
{
	int		i;
	float	dist;
	int		npc_in_range;

	i = 0;
	npc_in_range = 0;
	while (i < game->npc_count)
	{
		dist = vec3_distance(game->player.position, game->npcs[i].position);
		if (dist < INTERACTION_RANGE)
			manage_interaction(game, i, &npc_in_range);
		i++;
	}
	if (!npc_in_range)
	{
		game->interaction.npc_id = -1;
		game->interaction.count = 0;
	}
}*/
