/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:41:10 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/26 02:14:10 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	anim_tile_update(t_tile_animation *anim, t_game *game)
{
	anim->actual_frame = fmodf(anim->actual_frame
		+ anim->frame_time, anim->frames_num);
	game->textures[anim->type] = anim->frames[(int)anim->actual_frame];
}

t_index_animation	anim_index_init(size_t start_index, size_t end_index,
						float time_per_frame, float repeating)
{
	t_index_animation	result;

	result.actual_index	= start_index;
	result.start_index = start_index;
	result.end_index = end_index;
	result.time_per_frame = time_per_frame;
	result.repeating = repeating;
	result.anim_dir = 1;
	result.reversing = false;
	return (result);
}

void	anim_index_update(t_index_animation *anim)
{
	if (!anim->repeating && anim->actual_index >= anim->end_index)
		return ;
	anim->actual_index += anim->time_per_frame * anim->anim_dir;
	if (anim->repeating)
	{
		if (anim->reversing)
		{
			if (anim->actual_index >= anim->end_index)
			{
				anim->actual_index = anim->end_index;
				anim->anim_dir = -1;
			}
			else if (anim->actual_index <= anim->start_index)
			{
				anim->actual_index = anim->start_index;
				anim->anim_dir = 1;
			}
		}
		else
			anim->actual_index = anim->start_index + fmodf(anim->actual_index
				- anim->start_index + anim->time_per_frame, anim->end_index - anim->start_index);
	}
	else if (anim->actual_index > anim->end_index)
		anim->actual_index = anim->end_index;
}

bool	anim_index_is_ended(t_index_animation *anim)
{
	if (anim->anim_dir >= 0)
		return (anim->actual_index >= anim->end_index);
	else
		return (anim->actual_index <= anim->start_index);
}
