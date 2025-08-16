/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:33:46 by halnuma           #+#    #+#             */
/*   Updated: 2025/08/14 15:13:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_npc_text(t_game *game, t_npc *npc, int index)
{
	int		i;
	int		line_count;
	int		temp;
	int		size;
	char	**npc_text;

	line_count = 0;
	i = -1;
	while (++i < index)
	{
		while (game->npc_text[line_count] && \
			ft_strcmp(game->npc_text[line_count], "\n"))
			line_count++;
		line_count++;
	}
	temp = line_count;
	while (game->npc_text[temp] && ft_strcmp(game->npc_text[temp], "\n"))
		temp++;
	size = temp - line_count;
	npc_text = (char **)malloc(sizeof(char *) * size);
	i = -1;
	while (++i < size - 1)
		npc_text[i] = ft_strdup(game->npc_text[i + line_count + 1]);
	npc_text[size - 1] = NULL;
	npc->text = npc_text;
}

int	check_player(t_game *game, int i, int j, int *player)
{
	if (player_tile(game->file_content[i][j]))
	{
		if (*player)
			return (0);
		game->player.position.x = (double)j + 0.5;
		game->player.position.y = (double)(i - 8) + 0.5;
		if (game->file_content[i][j] == 'S')
			game->player.yaw_rad = M_PI / 2;
		else if (game->file_content[i][j] == 'N')
			game->player.yaw_rad = 3 * M_PI / 2;
		else if (game->file_content[i][j] == 'W')
			game->player.yaw_rad = M_PI;
		else if (game->file_content[i][j] == 'E')
			game->player.yaw_rad = 0;
		rad_to_vect(&game->player.direction, game->player.yaw_rad);
		*player = 1;
	}
	return (1);
}

int	check_enemies(t_game *game, int i, int j, int *e)
{
	if (game->file_content[i][j] == 'M')
	{
		if (game->enemy_count >= MAX_ENEMIES)
			return (0);
		game->enemies[*e].position.x = (double)j + 0.5;
		game->enemies[*e].position.y = (double)(i - 8) + 0.5;
		game->enemies[*e].hp = 100;
		game->enemies[*e].state = SLEEPING;
		game->enemy_count++;
		(*e)++;
	}
	return (1);
}

int	check_npcs(t_game *game, int i, int j, int *p)
{
	if (game->file_content[i][j] == 'P')
	{
		if (game->npc_count >= MAX_PNJ)
			return (0);
		game->npcs[*p].position.x = (double)j + 0.5;
		game->npcs[*p].position.y = (double)(i - 8) + 0.5;
		game->npcs[*p].position.z = 0.3f + 0.5;
		game->npc_count++;
		assign_npc_text(game, &game->npcs[*p], *p);
		(*p)++;
	}
	return (1);
}
