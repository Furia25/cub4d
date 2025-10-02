/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:07:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/30 15:08:35 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "fcntl.h"

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
	const float	half = 0.5f;

	return ((t_vec3){(bbox.min.x + bbox.max.x) * half,
		(bbox.min.y + bbox.max.y) * half,
		(bbox.min.z + bbox.max.z) * half});
}
