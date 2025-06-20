/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_textures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:20:57 by halnuma           #+#    #+#             */
/*   Updated: 2025/06/20 11:06:09 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TEXTURE_H
# define CUB3D_TEXTURE_H

typedef enum e_texture_type
{
	TEXTURE_NAN,
	TEXTURE_WALL,
	TEXTURE_EAST,
	TEXTURE_WEST,
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_TEST,
	TEXTURE_MAX_COUNT
}	t_texture_type;

typedef enum e_sprite_type
{
	SPRITE_ENEMY,
	SPRITE_MAX_COUNT
}	t_sprite_type;

#endif