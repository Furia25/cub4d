/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:33:46 by halnuma           #+#    #+#             */
/*   Updated: 2025/07/17 15:04:50 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_pnj_text(t_game *game, t_pnj *pnj, int index)
{
	int		i;
	int		line_count;
	int		tmp_count;
	int		size;
	char	**pnj_text;

	line_count = 0;
	i = -1;
	while (++i < index)
	{
		while (game->pnj_text[line_count] && \
			ft_strcmp(game->pnj_text[line_count], "\n"))
			line_count++;
		line_count++;
	}
	tmp_count = line_count;
	while (game->pnj_text[tmp_count] && \
   		ft_strcmp(game->pnj_text[tmp_count], "\n"))
		tmp_count++;
	size = tmp_count - line_count;
	pnj_text = (char **)malloc(sizeof(char *) * size);
	i = -1;
	while (++i < size - 1)
		pnj_text[i] = ft_strdup(game->pnj_text[i + line_count + 1]);
	pnj_text[size - 1] = NULL;
	pnj->text = pnj_text;
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
			game->player.rad_direction = M_PI / 2;
		else if (game->file_content[i][j] == 'N')
			game->player.rad_direction = 3 * M_PI / 2;
		else if (game->file_content[i][j] == 'W')
			game->player.rad_direction = M_PI;
		else if (game->file_content[i][j] == 'E')
			game->player.rad_direction = 0;
		rad_to_vect(&game->player.direction, game->player.rad_direction);
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

int	check_pnjs(t_game *game, int i, int j, int *p)
{
	if (game->file_content[i][j] == 'P')
	{
		if (game->pnj_count >= MAX_PNJ)
			return (0);
		game->pnjs[*p].position.x = (double)j + 0.5;
		game->pnjs[*p].position.y = (double)(i - 8) + 0.5;
		game->pnjs[*p].position.z = 0.3f + 0.5;
		game->pnj_count++;
		assign_pnj_text(game, &game->pnjs[*p], *p);
		(*p)++;
	}
	return (1);
}
