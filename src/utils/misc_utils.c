/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:07:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/28 18:29:46 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fcntl.h"

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

uint64_t	get_seed(void)
{
	ssize_t		len;
	uint64_t	result;
	int			file_fd;

	file_fd = open(SEED_SYSTEM_RAND_FILE, O_RDONLY);
	if (file_fd == -1)
	{
		printf(WARNING_PREFIX WARNING_SEED, (uint64_t)SEED_FALLBACK_DEFAULT);
		return ((uint64_t)SEED_FALLBACK_DEFAULT);
	}
	len = read(file_fd, &result, sizeof(result));
	close(file_fd);
	if (len < (long) sizeof(result))
	{
		printf(WARNING_PREFIX WARNING_SEED, (uint64_t)SEED_FALLBACK_DEFAULT);
		return ((uint64_t)SEED_FALLBACK_DEFAULT);
	}
	printf(INFO_PREFIX SEED_MESSAGE, result);
	return (result);
}

bool	is_pixel_valid(int x, int y, t_img_data *img)
{
	return (!(x < 0 || x > img->width || y < 0 || y > img->height));
}

t_vec3	bbox_get_center(t_bbox bbox)
{
	return ((t_vec3){(bbox.min.x + bbox.max.x) * 0.5,
		(bbox.min.y + bbox.max.y) * 0.5,
		(bbox.min.z + bbox.max.z) * 0.5});
}
