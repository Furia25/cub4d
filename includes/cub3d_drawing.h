/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_drawing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 23:02:52 by vdurand           #+#    #+#             */
/*   Updated: 2025/10/01 10:30:58 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DRAWING_H
# define CUB3D_DRAWING_H
# include "crazypng.h"
# include "maths2_geometry.h"
# include "cub3d_structs.h"

/*TEMP*/
static inline t_rgba8	rgba8(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((t_rgba8){{b, g, r, a}});
}

void	draw_pixel(t_rgba8 rgba, unsigned int x,
							unsigned int y, t_img_data *img);
void	draw_spr_sheet(t_draw_transform tform, size_t index,
							t_sprite_sheet *sprite, t_img_data *img);
void	draw_rect(t_rgba8 rgba, t_rect rectangle, t_img_data *img);

#endif