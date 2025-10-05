/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:13:59 by halnuma           #+#    #+#             */
/*   Updated: 2025/10/05 16:42:11 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	tab_length(void **tab)
{
	size_t	count;

	if (!tab)
		return (0);
	count = 0;
	while (*tab)
	{
		tab++;
		count++;
	}
	return (count);
}

char	**chartab_dup(char **tab, size_t height)
{
	char	**result;
	size_t	y;

	y = 0;
	result = ft_calloc((height + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (y < height)
	{
		result[y] = ft_strdup(tab[y]);
		if (!result[y])
			break ;
		y++;
	}
	if (y < height)
	{
		while (y > 0)
			free(result[--y]);
		free(result);
		return (NULL);
	}
	return (result);
}

void	free_tab(void **map)
{
	if (!map)
		return ;
	free_tab_content(map);
	free(map);
}

void	free_tab_content(void **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
}
