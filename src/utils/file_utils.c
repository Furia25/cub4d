/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:49:57 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/28 21:50:11 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_file_valid(char *path)
{
	int	temp_fd;

	if (!path)
		return (false);
	temp_fd = open(path, O_RDONLY);
	if (temp_fd == -1)
		return (false);
	close(temp_fd);
	return (true);
}

int	file_length(char *file)
{
	int				fd;
	int				length;
	t_gnl_result	line;

	length = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-2);
	line = get_next_line(fd);
	while (!line.error)
	{
		length++;
		if (line.ended)
			break ;
		free(line.line);
		line = get_next_line(fd);
	}
	free(line.line);
	close(fd);
	if (line.error)
		return (-1);
	else
		return (length);
}
