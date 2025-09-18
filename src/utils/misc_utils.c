/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:07:59 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/18 17:37:18 by vdurand          ###   ########.fr       */
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

void	update_anim(t_animated_tiles *anim, t_game *game)
{
	anim->actual_frame = fmodf(anim->actual_frame
		+ anim->frame_time, anim->frames_num);
	game->textures[anim->type] = anim->frames[(int)anim->actual_frame];
}
