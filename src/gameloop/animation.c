/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:41:10 by vdurand           #+#    #+#             */
/*   Updated: 2025/09/28 22:33:55 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_animation	anim_init(size_t start_index, size_t end_index,
						float time_per_frame, float repeating)
{
	t_animation	result;

	result.actual_index = start_index;
	result.start_index = start_index;
	result.end_index = end_index;
	result.time_per_frame = time_per_frame;
	result.repeating = repeating;
	result.anim_dir = 1;
	result.reversing = false;
	return (result);
}

void	anim_update(t_animation *anim)
{
	if (!anim->repeating && anim_is_ended(anim))
		return ;
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
	else if (anim->actual_index > anim->end_index)
	{
		anim->actual_index = anim->start_index;
	}
	anim->actual_index += anim->time_per_frame * anim->anim_dir;
}

bool	anim_is_ended(t_animation *anim)
{
	if (anim->anim_dir >= 0)
		return (anim->actual_index >= anim->end_index);
	else
		return (anim->actual_index <= anim->start_index);
}

void	anim_reset(t_animation *anim)
{
	if (anim->anim_dir >= 0)
		anim->actual_index = anim->start_index;
	else
		anim->actual_index = anim->end_index;
}

void	anim_tile_update(t_tile_animation *anim, t_game *game)
{
	size_t	index;

	anim_update((t_animation *) anim);
	index = (int)anim->index.actual_index;
	game->textures[anim->type] = game->textures[index];
}
